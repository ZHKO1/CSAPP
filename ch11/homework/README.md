代码具体参见example/tiny_web/tiny_homework.c

## 11.6
A. 现有代码已经支持（作者可能是指请求头是啥，响应头也返回啥）
B. 
Accepted connection from (localhost, 45544)
Request headers: 
GET / HTTP/1.1
Connection: keep-alive
Pragma: no-cache
Cache-Control: no-cache
sec-ch-ua: "Chromium";v="116", "Not)A;Brand";v="24", "Google Chrome";v="116"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9

Response headers: 
HTTP/1.0 200 OK
Server: Tiny Web Server
Connection: close
Content-length: 615
Content-type: text/html

C. chrome 116版本用的 HTTP/1.1
D. https://www.rfc-editor.org/rfc/rfc2616.pdf

## 11.8
信号相关函数我忘得差不多了...还是先复习第八章再回来做这道题吧...

## 11.11
虽然11.5.4的旁注提示重定向标准输入到已连接描述符，但实际上如果跟着示例用了rio_readline就不太合适用重定向这方案了，只能rio_readnb用到底了。
CGI环境变量我多加了POST_BODY来解决传递请求体的问题。也只能这样了
