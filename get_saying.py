import requests 

def ISay():
    url = "https://www.iamwawa.cn/home/lizhi/ajax"
    header = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                      'Chrome/98.0.4758.139 Safari/537.36 '
    }
    r = requests.get(url=url, headers=header)
    r = r.json()
    txt = r["data"]
    
    return txt

if __name__ == "__main__":
    r = ISay()
    with open("./isay.txt",'w', encoding="gbk") as f:
        f.write(r)
