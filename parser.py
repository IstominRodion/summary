from bs4 import BeautifulSoup
from urllib.request import *
import re
import json
import os
import datetime
import zipfile

def get_tag(class_name, needed_tag, soup):
	"""Возвращает текст тэга с нужной информацией."""
	ret_tag = None
	for tag in soup.find_all(re.compile(needed_tag)):
		try:
			if tag["class"] == class_name:
				ret_tag = tag
				break
		except KeyError:
			continue
		except ValueError:
			continue
	try:
		return ret_tag.get_text()
	except AttributeError:
		return ""

def get_max_page(url):
	"""Возвращает число страниц с вакансиями."""
	max_page = 1
	url = url + "1"

	html = get_html(url)
	soup = BeautifulSoup(html, 'lxml')

	for tag in soup.find_all(re.compile("^span")):
		try:
			if tag['class'] == ["_3IDf-"] and tag.get_text().isdigit():
				if int(tag.get_text()) > max_page:
					max_page = int(tag.get_text())
		except KeyError:
			continue
		except ValueError:
			continue
		except IndexError:
			continue

	return max_page

def get_html(url):
	"""Возвращает html страницы."""
	req = Request(url)
	html = urlopen(req).read()
	return html

def get_refs(soup):
	"""Возвращает список ссылок на вакансии."""
	count = 0
	refs_list = []
	for tag in soup.find_all(re.compile("^a")):
		if tag["class"][1] == "_6AfZ9":
			refs_list.append(tag["href"])
	return refs_list

def get_json(url, file_name):
	"""Собирает информацию из тэгов и записывает её в json."""

	# Названия классов и тэги для поиска нжуных полей в супе
	class_name_id = ["_3mfro", "_9fXTd", "_2JVkc", "_2VHxz"]
	tag_id = "^span"
	class_name_title = ["_3mfro", "rFbjy", "s1nFK", "_2JVkc"]
	tag_title = "^h1"
	class_name_location = ["_3mfro", "_1hP6a", "_2JVkc"]
	tag_location = "^span"
	class_name_employer = ["_3mfro", "PlM3e", "_2JVkc", "_2VHxz", "_3LJqf", "_15msI"]
	tag_employer = "^h2"
	class_name_description = ["_3mfro", "_2LeqZ", "_1hP6a", "_2JVkc", "_2VHxz", "_15msI"]
	tag_description = "^span"
	
	html_vac = get_html(url)
	soup_vac = BeautifulSoup(html_vac, 'lxml')

	vacancy = {"id" : get_tag(class_name_id, tag_id, soup_vac)[2:10],
	"title" : get_tag(class_name_title, tag_title, soup_vac),
	"location" : get_tag(class_name_location, tag_location, soup_vac),
	"employer" : get_tag(class_name_employer, tag_employer, soup_vac),
	"ref" : url,
	"desctiption" : get_tag(class_name_description, tag_description, soup_vac)}
	
	with open(file_name, "a", encoding = "utf-8") as f:
		json.dump(vacancy, f, ensure_ascii = False, indent = 2)
	
def main():
	print("---Парсер вакансий с superjob---")
	
	opener = build_opener()
	install_opener(opener)

	with open('regions.json', 'r', encoding = 'utf-8') as f:
		regions = json.load(f)

		now = datetime.datetime.now()
		z = zipfile.ZipFile(str(now.date()) + '.zip', 'w')
		
		for region in regions:
			file_name = region["region"] + "_vacancies.json"
			open(file_name, "w", encoding = "utf-8")
						
			print("---Работаю с " + region["region"] + "---")
			max_page = get_max_page(region["ref"])
			print("---Количество страниц равно " + str(max_page) + "---")

			refs_list = []

			for i in range(max_page):
				print("---Получаю ссылки со страницы " + str(i + 1)+"---")
				html_list_vac = get_html(region["ref"] + str(i + 1))
				soup = BeautifulSoup(html_list_vac, 'lxml')
				refs_list.extend(get_refs(soup))
				print("---Получено ссылок " + str(len(refs_list)) + "---")

			print("---Выгружаю в json---")
			num = 0
			for i in refs_list:
				get_json("https://superjob.ru" + i, file_name)
				num += 1
				print("---Выгружено " + str(num) + " вакансий---")
			
			z.write(file_name)
			os.remove(file_name)

		z.close()

main()