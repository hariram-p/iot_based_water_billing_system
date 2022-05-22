from flask import Flask,render_template,request, url_for
import urllib
from urllib.request import urlopen
import json
import smtplib 
from email.mime.multipart import MIMEMultipart 
from email.mime.text import MIMEText 
from email.mime.base import MIMEBase 
from email import encoders
import time

READ_API_KEY='5QUWLJCW6CKBHESJ'
CHANNEL_ID='1700175'


app = Flask(__name__)

def report_send_mail1(body_, to):
    fromaddr = "iotwaterbillingsystemowner@gmail.com"
    toaddr = to
    msg = MIMEMultipart() 
    msg['From'] = fromaddr 
    msg['To'] = toaddr 
    msg['Subject'] = 'Water Biling System'
    body = body_
    msg.attach(MIMEText(body, 'plain')) 
    s = smtplib.SMTP('smtp.gmail.com', 587) 
    s.starttls() 
    s.login(fromaddr, "Iotproject2022") 
    text = msg.as_string() 
    s.sendmail(fromaddr, toaddr, text) 
    s.quit()

old1 = []
old2 = []
@app.route('/')
def main():
    global c
    conn = urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" \
        % (CHANNEL_ID,READ_API_KEY))
    response = conn.read()
    # print ("http status code=%s" % (conn.getcode()))
    # print (data['field1'],data['created_at'])
    data=json.loads(response)
    result = str(data['field1']).strip()
    text = result.split('_')
    # print(text)
    j = 0
    b = []
    c = []
    for i in text:
        if j<4:
            b.append(i)
            j += 1
            if len(b) == 4:
                c.append(b)
                b = []
                j = 0
    conn.close()
    # print(c)
    # i = 1
    # for a in c:
    #     if i == 1:
    #         if a[1] not in old1:
    #             old1.append(a[1])
    #             body_ = str(a)
    #             to = 'iotwaterbillingsystemhouse1@gmail.com'
    #             i += 1
    #             report_send_mail1(body_, to)
    #     elif i == 2:
    #         if a[1] not in old2:
    #             old2.append(a[1])
    #             body_ = str(a)
    #             to = 'iotwaterbillingsystemhouse2@gmail.com'
    #             i = 1
    #             report_send_mail1(body_, to)

    return render_template('/index.html',data=c)

@app.route('/upload',methods=['POST','GET'])
def upload():
    result = c
    if request.method == 'POST':
        value = request.form.get('filename')
        for i in c:
            if i[0] == value:
                d = 'Consumption : ' +str(i[1])
                f = 'Price : ' +str(i[3])

    return render_template('/index.html',msg1=d,msg2=f,h=value)

if __name__ == '__main__':
    while True:
        app.run(debug=True,port=4000)