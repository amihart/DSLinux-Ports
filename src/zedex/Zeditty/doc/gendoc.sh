cat ../include/zeditty.h | sed "/__REPLACE/{
r /dev/stdin
d
}" doc.template > doc.html

#phantomjs no longer maintained, changing to wkhtml
# export QT_QPA_PLATFORM=offscreen
# export QT_QPA_FONTDIR=/usr/share/fonts/truetype/dejavu/
# phantomjs --ignore-ssl-errors=true --ssl-protocol=any --ssl-ciphers=ALL --debug=yes convert.js
wkhtmltoimage doc.html doc.png
