#!/bin/python

# 
# Monitor price of Macbook Pro MC700 ZH/A
# and send message to myself
# reflesh in 60 seconds
#
# 2011-07-04 urllib
# 2011-07-06 httplib2
#

import string
import time
import subprocess
import httplib2
import getpass

value = '8,198.00'
value = '0'

key = "priceLarge"
link = '''
http://www.amazon.cn/gp/product/B004PYEGE8/ref=s9_simh_gw_p147_d6_i1?pf_rd_m=A1AJ19PSB66TGU&pf_rd_s=center-3&pf_rd_r=0XYFYMH4XMWKQZBMCFD0&pf_rd_t=101&pf_rd_p=58223172&pf_rd_i=899254051
'''

h = httplib2.Http('.cache')
phone = raw_input("Phone number: ")
pwd = getpass.getpass("Pwd: ")
while(1):
    response, content = h.request(link)
    pos = content.find(key)+len(key)+6
    x = content[pos:pos+8]

    if value != x:
        value = x
        subprocess.Popen("cliofetion -f %s -p %s -t %s -d 'Macbook Pro mc700 %s'" % 
            phone, pwd, phone, value, shell=True)

    time.sleep(60)
