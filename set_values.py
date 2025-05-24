import requests
import sys


first_delay = sys.argv[1]
second_delay = sys.argv[2]
note_vals = sys.argv[3] # Try to match note waveforms?

if note_vals == "":
    resp = requests.get("http://192.168.1.131/{0}SETFIRST".format(first_delay))
    print(resp.status_code)
    resp = requests.get("http://192.168.1.131/{0}SETSECOND".format(second_delay))
    print(resp.status_code)

else:
    resp = requests.get("http://192.168.1.131/{0}NOTEVALS".format(note_vals))
    print(resp.status_code)
