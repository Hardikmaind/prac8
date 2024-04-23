
import requests
import base64
endpoint="https://api.github.com/repos/Hardikmaind/prac8/contents/demo.py"
res=requests.get(endpoint)
data=res.json()

if 'content' in data:
    code=base64.b64decode(data['content']).decode('utf-8')
    print(code)
