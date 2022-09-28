import requests 

def ISay():
    url = "https://v.api.aa1.cn/api/yiyan/index.php"
    r = requests.get(url=url)
    r = r.text
    r = r.replace("<p>", "").replace("</p>", "")
    print(r)
    
    return r


if __name__ == "__main__":
    r = ISay()

    print(r)
