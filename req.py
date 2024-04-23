
import requests
import base64
endpoint="https://api.github.com/repos/Hardikmaind/prac8/contents/ASS1.ipynb"
res=requests.get(endpoint)
data=res.json()

if 'content' in data:
    code=base64.b64decode(data['content']).decode('utf-8')
    print(code)
