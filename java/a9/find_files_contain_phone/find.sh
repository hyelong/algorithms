# 在文件夹下找出所有包涵电话号码的文件 (grep 和 regular expression)

find . -type f | xargs grep -P '\d{3}[\s\-]{0,1}\d{3}[\s\-]\d{4}'|cut -d':' -f1 | uniq
