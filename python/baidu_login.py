# _*_ coding:utf-8 _*_
# name login_baidu.py

import urllib,urllib2,httplib,cookielib

def auto_login_hi(url,name,pwd):
    url_hi="http://passport.baidu.com/?login"
    #设置cookie
    cookie=cookielib.CookieJar()
    cj=urllib2.HTTPCookieProcessor(cookie)
    #设置登录参数
    postdata=urllib.urlencode({'username':name,'password':pwd})
    #生成请求
    request=urllib2.Request(url_hi,postdata)
    #登录百度
    opener=urllib2.build_opener(cj)
    f=opener.open(request)
    print f
    #打开百度HI空间页面
    hi_html=opener.open(url)
    return hi_html
if __name__=='__main__':
    name='hjkll'
    password='11111111'
    url='http://hi.baidu.com/郑森林'
    h=auto_login_hi(url,name,password)
    print h.read()
