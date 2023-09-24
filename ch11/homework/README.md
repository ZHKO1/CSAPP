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
信号我又忘差不多了...又得重温第八章了

## 11.12
虽然11.5.4的旁注提示重定向标准输入到已连接描述符，但实际上如果跟着示例用了rio_readline就不太合适用重定向这方案了，只能rio_readnb用到底了。
CGI环境变量我多加了POST_BODY来解决传递请求体的问题。也只能这样了

## 11.13
我的想法是在信号处理函数里非本地跳转来直接跳到回收内存资源阶段，再进行下一个accept阶段
麻烦的是似乎无法测试，找了个大容量视频，结果浏览器一直在loading中，所以看不到所谓的SIGPIPE信号导致进程终止现象，所以也无法验证现象是否能解决。

## 总结
tinyweb原代码测下来有个很奇怪的问题
就是浏览器发起请求获取页面，也拿到返回，服务端在终端的输出也符合预期。按理来说本次连接应该就此结束，但服务端输出最后多了一条Accepted connection from (%s, %s)，看现象应该是浏览器额外发起connection，但是没有发送任何字节。本来猜测原因跟Http1.1有关，比如浏览器发起的请求头包含Connect: keep-alive，但是响应头已经包含Connect: close，按照我的理解，浏览器收到这个响应头就不要再发connection了，赶紧结束事务完事。但依然还有Accepted日志。所以依然无从得知真正的原因

除此之外，在最后一次accept成功后，如果浏览器不做任何操作，服务端的日志会疯狂循环输出。这里我能做的是基于源代码增强了点健壮性，相关字符串使用前先清0，修复了该问题。

主要奇怪的是为何网上没人提到原代码的问题？
