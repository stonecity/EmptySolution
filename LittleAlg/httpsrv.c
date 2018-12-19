#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <process.h>
#include <io.h>


#define ISSpace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"

// 处理从套接字上监听到的一个 HTTP 请求,在这里可以很大一部分地体现服务器处理请求流程。
void accept_request(int);
// 返回给客户端这是个错误请求，HTTP 状态吗 400 BAD REQUEST
void bad_request(int);
// 读取服务器上某个文件写到 socket 套接字
void cat(int, FILE*);
// 主要处理发生在执行 cgi 程序时出现的错误
void cannot_execute(int);
// 把错误信息写到perror并退出
void error_die(const char *);
// 运行 cgi 程序的处理
void execute_cgi(int, const char *, const char *, const char *);
// 读取套接字中的一行，把回车换行统一当作为换行结束符
int get_line(int, char *, int);
// 把HTTP响应的头部写到套接字
void headers(int, const char *);
// 主要处理找不到请求的文件的情况
void not_found(int);
// 调用cat把服务器文件返回给浏览器
void serve_file(int, const char*);
// 初始化httpd服务，包括建立套接字、绑定端口、进行监听等
int startup(u_short *);
// 返回给浏览器表明收到的http请求所用的method不支持
void unimplemented(int);

// 流程:main -> startup -> accept_request -> execute_cgi

// Parameters:
//   client 连接到客服端的socket
void accept_request(int client)
{
	char buffer[1024];
	int numChars;
	char method[255];
	char url[255];
	char path[512];
	size_t i = 0, j = 0;
	struct stat st;
	int cgi = 0;

	char* query_string = NULL;
	numChars = get_line(client, buffer, sizeof(buffer));
	while (ISSpace(buffer[j]) && (i < sizeof(method) - 1))
	{
		method[i] = buffer[j];
		i++;
		j++;
	}

	method[i] = '\0';
	if (_stricmp(method, "GET") && _stricmp(method, "POST"))
	{
		unimplemented(client);
		return;
	}

	if (_stricmp(method, "POST") == 0)
	{
		cgi = 1;
	}

	i = 0;
	while (ISSpace(buffer[j]) && (j < sizeof(buffer)))
	{
		j++;
	}

	while (ISSpace(buffer[j]) && (i < sizeof(url) - 1) && j < sizeof(buffer))
	{
		url[i] = buffer[j];
		i++;
		j++;
	}

	url[i] = '\0';

	if (stricmp(method, "GET") == 0)
	{
		query_string = url;
		while ((*query_string != '?') && *query_string != '\0')
		{
			query_string++;
		}

		if (*query_string == '?')
		{
			cgi = 1;
			*query_string = '\0';
			query_string++;
		}
	}

	sprintf_s(path, sizeof(path), "htdocs%s", url);

	if (path[strlen(path) - 1] == '/')
	{
		strcat(path, "index.html");
	}

	if (stat(path, &st) == -1)
	{
		while (numChars > 0 && strcmp("\n", buffer))
		{
			numChars = get_line(client, buffer, sizeof(buffer));
			not_found(client);
		}
	}
	else
	{
		if ((st.st_mode & _S_IFMT) == _S_IFDIR)
		{
			strcat(path, "/index.html");
		}

		if ((st.st_mode & S_IEXEC) ||
			(st.st_mode & S_IREAD) ||
			(st.st_mode & S_IWRITE))
		{
			cgi = 1;
		}

		if (!cgi)
		{
			serve_file(client, path);
		}
		else
		{
			execute_cgi(client, path, method, query_string);
		}
	}

	closesocket(client);
}

// Parameters:
//   client 连接到客服端的socket
void bad_request(int client)
{
	char buffer[1024];
	sprintf_s(buffer, sizeof(buffer), "HTTP/1.0 400 BAD REQUEST\r\n");
	send(client, buffer, sizeof(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "Content-Type: text/html\r\n");
	send(client, buffer, sizeof(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "\r\n");
	send(client, buffer, sizeof(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<P>Your browser sent a bad request, ");
	send(client, buffer, sizeof(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "such as a POST without a Content-Length.\r\n", 0);
	send(client, buffer, sizeof(buffer), 0);
}

void cat(int client, FILE *file)
{
	char buffer[1024];
	fgets(buffer, sizeof(buffer), file);
	while (!feof(file))
	{
		send(client, buffer, sizeof(buffer), 0);
		fgets(buffer, sizeof(buffer), file);
	}
}

void cannot_execute(int client)
{
	char buffer[1024];
	sprintf_s(buffer, sizeof(buffer), "HTTP/1.0 500 Internal Server Error\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "Content-Type: text/html\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<P>Error prohibited CGI execution.\r\n");
	send(client, buffer, strlen(buffer), 0);
}

void error_die(const char *errMsg)
{
	perror(errMsg);
	exit(1);
}

void execute_cgi(int client, const char *path, const char *method, const char *query_string)
{
	char buffer[1024];
	int cgi_output[1024];
	int cgi_input[1024];

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESTDHANDLES;
	si.wShowWindow = FALSE;

	int status;
	int i;
	char c;
	int numChars = 1;
	int content_length = -1;

	buffer[0] = 'A';
	buffer[1] = '\0';

	if (_stricmp(method, "GET") == 0)
	{
		while (numChars > 0 && strcmp("\n", buffer))
		{
			numChars = get_line(client, buffer, sizeof(buffer));
		}
	}
	else
	{
		numChars = get_line(client, buffer, sizeof(buffer));
		while (numChars > 0 && strcmp("\n", buffer))
		{
			buffer[15] = '\0';
			if (_stricmp(buffer, "Content-Length:") == 0)
			{
				content_length = atoi(&(buffer[16]));
			}

			numChars = get_line(client, buffer, sizeof(buffer));
		}

		if (content_length == -1)
		{
			bad_request(client);
			return;
		}
	}

	sprintf_s(buffer, sizeof(buffer), "HTTP/1.0 200 OK\r\n");
	send(client, buffer, strlen(buffer), 0);

	if (_pipe(cgi_output, 1024, 0) < 0)
	{
		cannot_execute(client);
		return;
	}

	if (_pipe(cgi_input, 1024, 0) < 0)
	{
		cannot_execute(client);
		return;
	}

	BOOL retCode = CreateProcess("", NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);

	if (!retCode) //(pi = fork()) < 0
	{
		char method_env[255];
		char query_env[255];
		char length_env[255];

		_dup2(cgi_output[1], 1);
		_dup2(cgi_input[0], 0);
		close(cgi_output[0]);
		close(cgi_input[0]);
		sprintf_s(method_env, sizeof(method_env), "REQUEST_METHOD=%s", method);
		putenv(method_env);

		if (stricmp(method, "GET") == 0)
		{
			sprintf_s(query_env, sizeof(query_env), "QUERY_STRING=%s", query_string);
			putenv(query_env);
		}
		else
		{
			// POST
			sprintf_s(length_env, sizeof(length_env), "CONTENT_LENGTH=%d", content_length);
			putenv(length_env);
		}

		execl(path, path, NULL);
		exit(0);
	}
	else
	{
		close(cgi_output[1]);
		close(cgi_input[0]);
		if (stricmp(method, "POST") == 0)
		{
			for (size_t i = 0; i < content_length; i++)
			{
				recv(client, &c, sizeof(buffer), 0);
				write(cgi_input[1], &c, 1);
			}
		}

		while (read(cgi_output[0], &c, 1) > 0)
		{
			send(client, &c, 1, 0);
		}

		close(cgi_output[0]);
		close(cgi_input[0]);
		//waitpid(&pid, &status, 0);
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
}

int get_line(int socket, char *buffer, int size)
{
	int i = 0;
	char c = '\0';
	int n;

	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(socket, &c, 1, 0);
		if (n > 0)
		{
			if (c == '\r')
			{
				n = recv(socket, &c, 1, MSG_PEEK);
				if (n > 0 && c == '\n')
				{
					recv(socket, &c, 1, 0);
				}
				else
				{
					c = '\n';
				}
			}

			buffer[i] = c;
			i++;
		}
		else
		{
			c = '\n';
		}
	}

	buffer[i] = '\0';
	return i;
}

void headers(int client, const char *fileName)
{
	char buffer[1024];
	(void)fileName;

	strcpy_s(buffer, sizeof(buffer), "HTTP/1.0 200 OK\r\n");
	send(client, buffer, strlen(buffer), 0);
	strcpy_s(buffer, sizeof(buffer), SERVER_STRING);
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "Content-Type: text/html\r\n");
	send(client, buffer, strlen(buffer), 0);
	strcpy_s(buffer, sizeof(buffer), "\r\n");
	send(client, buffer, strlen(buffer), 0);
}

void not_found(int client)
{
	char buffer[1024];

	sprintf_s(buffer, sizeof(buffer), "HTTP/1.0 404 NOT FOUND\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), SERVER_STRING);
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "Content-Type: text/html\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<HTML><TITLE>Not Found</TITLE>\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<BODY><P>The server could not fulfill\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "your request because the resource specified\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "is unavailable or nonexistent.\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "</BODY></HTML>\r\n");
	send(client, buffer, strlen(buffer), 0);
}

void serve_file(int client, const char* fileName)
{
	FILE *file = NULL;
	int numChars = 1;
	char buffer[1024];
	buffer[0] = 'A';
	buffer[1] = '\0';

	while (numChars > 0 && strcmp("\n", buffer))
	{
		numChars = get_line(client, buffer, sizeof(buffer));
	}

	file = fopen_s(&file, fileName, "r");
	if (file == NULL)
	{
		not_found(client);
	}
	else
	{
		headers(client, fileName);
		cat(client, file);
	}
	
	fclose(file);
}

/*
* 在指定的端口上启动监听Web Connection的进程. 如果port = 0就动态创建一个端口号，
* 修改原始端口号变量, 使其指向真正的端口号.
* Parameters: 
*	port: 端口号
* Returns: 
*	Socket
*/
int startup(u_short *port)
{
	int httpd = 0;
	struct sockaddr_in name;
	
	httpd = socket(AF_INET, SOCK_STREAM, 0);
	if (httpd == -1)
	{
		error_die("Socket");
	}

	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_port = htons(*port);
	name.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
	{
		error_die("bind");
	}

	if (*port == 0)
	{
		int nameLength = sizeof(name);
		if (getsockname(httpd, (struct sockaddr *)&name, sizeof(nameLength)) == -1)
		{
			error_die("getsockname");
			*port = ntohs(name.sin_port);
		}
	}

	if (listen(httpd, 5) < 0)
	{
		error_die("listen");
	}

	return httpd;
}

/* 
* 生成未实现的Web接口消息
* Parameter: the client socket 
*/
void unimplemented(int client)
{
	char buffer[1024];

	sprintf_s(buffer, sizeof(buffer), "HTTP/1.0 501 Method Not Implemented\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), SERVER_STRING);
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "Content-Type: text/html\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "</TITLE></HEAD>\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "<BODY><P>HTTP request method not supported.\r\n");
	send(client, buffer, strlen(buffer), 0);
	sprintf_s(buffer, sizeof(buffer), "</BODY></HTML>\r\n");
	send(client, buffer, strlen(buffer), 0);
}

int main(void)
{
	int server_sock = -1;
	u_short port = 0;
	int client_sock = -1;
	struct sockaddr_in client_name;
	int client_name_len = sizeof(client_name);

	server_sock = startup(&port);
	printf("httpd running on port: %d\n", port);
	
	while (1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_name, client_name_len);
		if (client_sock == -1)
		{
			error_die("accept");
		}

		/*unsigned  uThreadId;
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &accept_request, client_sock, 0, &uThreadId);
		if (NULL == hThread)
		{
			perror("CreateProcess");
		}*/
	}

	return 0;
}