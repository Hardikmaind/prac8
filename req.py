
import requests
import base64
endpoint="https://api.github.com/repos/Hardikmaind/prac8/contents/dl/ass1.txt"
res=requests.get(endpoint)
data=res.json()

if 'content' in data:
    code=base64.b64decode(data['content']).decode('utf-8')
    print(code)










#below is the another method no need to decode


import requests
print(requests.get("https://raw.githubusercontent.com/Hardikmaind/prac8/main/dl/ass1.txt").text)