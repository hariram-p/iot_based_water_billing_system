from urllib.request import urlopen
import json
import smtplib
from email.mime.multipart import MIMEMultipart 
from email.mime.text import MIMEText 
from email.mime.base import MIMEBase 
from email import encoders
import time


past1=0
past2=0

READ_API_KEY='5QUWLJCW6CKBHESJ'
CHANNEL_ID='1700175'

def mail(to,amount,price):
    fromaddr = "iotwaterbillingsystemowner@gmail.com"
    toaddr = to
    msg = MIMEMultipart()
    msg['From'] = fromaddr 
    msg['To'] = toaddr
    msg['Subject'] = 'WATER BILL'
    body = 'You have consumed another 10 liters Total water consumed  '+amount+'Liters price of '+price+'Rupees'
    msg.attach(MIMEText(body, 'plain'))
    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.starttls()
    s.login(fromaddr, "Iotproject2022")
    text = msg.as_string()
    s.sendmail(fromaddr, toaddr, text)
    print('mail is sent to ',to,'  ',amount)
    s.quit()
def report():
    global past1
    global past2
    conn = urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" \
        % (CHANNEL_ID,READ_API_KEY))
    response = conn.read()
    data=json.loads(response)
    result = str(data['field1']).strip()
    text = result.split('_')
    print(text)
    if past1<int(text[1]):
        mail('iotwaterbillingsystemhouse1@gmail.com',text[1],text[3])
    past1=int(text[1])
    if past2<int(text[5]):
        mail('iotwaterbillingsystemhouse2@gmail.com',text[5],text[7])
    past2=int(text[5])


while True:
    report()
    time.sleep(2)
