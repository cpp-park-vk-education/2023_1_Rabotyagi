# Указывает Docker использовать официальный образ python 3 с dockerhub в качестве базового образа
FROM python:3.10.6
# Устанавливает переменную окружения, которая гарантирует, что вывод из python будет отправлен прямо в терминал без предварительной буферизации
ENV PYTHONUNBUFFERED 1
# Устанавливает рабочий каталог контейнера — "app"
# WORKDIR /site-backend
COPY . .
# COPY requirements.txt .
# Запускает команду pip install для всех библиотек, перечисленных в requirements.txt
RUN pip install -r requirements.txt
RUN rm requirements.txt
# RUN mkdir -p media/files/
# RUN mkdir -p static