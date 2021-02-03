from tkinter import *
from tkinter import colorchooser
from random import randint
import numpy as np
import math

# Координаты прямой
line_x0 = 0
line_y0 = 0
m_line_x = 0
m_line_y = 0

# Настройки режима(рисование-перемещение)
mode = 'draw'

# Выбрана ли прямая в режиме перемещения
line_chosen = False

# Хэндлер текущей прямой в режиме перемещения
cur_line = 0

# Список с предыдущими прямыми
prev_lines = []

# Переключатель места перемещения
switch = ''

# Настройки цвета и толщины прямых
color = 'black'
line_width = 1.0

# Промежуточное множество для хранения прямых, объявляемых группой
gr = set()

# Флаг выбора группы
gr_chosen = False

# Матрица 2D преобразований
matrix = None

def preline(event):
	if mode == 'draw':
		preline_draw(event)
	if mode == 'move':
		preline_move(event)
	if mode == 'group':
		preline_group(event)
	if mode == 'rgroup':
		preline_rgroup(event)
	if mode == '2d':
		preline_2d(event)

def preline_draw(event):
	global line_x0, line_y0, cur_line
	line_x0 = event.x
	line_y0 = event.y
	cur_line = cnv.create_line(0,0,1,1,fill=color)

def preline_move(event):
	global cur_line, line_chosen
	if not line_chosen and cnv.find_withtag('current') != ():
		cur_line = cnv.find_withtag('current')[0]
		line_chosen = True
		cnv.itemconfig(cur_line, width = 1.5)
		if not is_group(cur_line):
				prev_lines.remove(cur_line)
				cnv.itemconfig(cur_line, width = 1.5)
		else:
			cur_line = sub_is_group(cur_line)
			prev_lines.remove(cur_line)
			for i in cur_line:
				i = cnv.itemconfig(i, width = 1.5)
		del_btn['state'] = 'normal'
	if line_chosen and not isinstance(cur_line,set):
		global switch, m_line_x, m_line_y

		m_line_x, m_line_y = event.x, event.y

		l = cnv.coords(cur_line)
		l = {'x0':l[0], 'y0':l[1], 'x1':l[2], 'y1':l[3]}

		if abs(l['x0'] - event.x) <= 2 and abs(l['y0'] - event.y) <= 2:
			switch = 'first'
		if abs(l['x1'] - event.x) <= 2 and abs(l['y1'] - event.y) <= 2:
			switch = 'second'
		if cnv.find_withtag('current') == (cur_line,) and abs(l['x1'] - event.x) > 2 and abs(l['x0'] - event.x) > 2:
			switch = 'line'
		if cnv.find_withtag('current') == ():
			line_chosen = False
			prev_lines.append(cur_line)
			del_btn['state'] = 'disabled'
			cnv.itemconfig(cur_line, width = 1.0)
	if line_chosen and isinstance(cur_line,set):
		m_line_x, m_line_y = event.x, event.y
		try:
		 	l = cnv.find_withtag('current')[0]
		except IndexError:
		 	l = -1
		if l != () and l in cur_line:
			switch = 'line'
		if l == -1:
			line_chosen = False
			prev_lines.append(cur_line)
			del_btn['state'] = 'disabled'
			for i in cur_line:
				cnv.itemconfig(i, width = 1.0)

def preline_group(event):
	if cnv.find_withtag('current') != ():
		global gr
		l = cnv.find_withtag('current')[0]
		if is_group(l):
			gr = gr.union(sub_is_group(l))
		else:
			gr.add(l)
		prev_lines.remove(sub_is_group(l))
		for i in gr:
			cnv.itemconfig(i, width = 1.5,fill='red')
		print (prev_lines)

def preline_rgroup(event):
	if cnv.find_withtag('current') != ():
		l = cnv.find_withtag('current')[0]
		if is_group(l):
			rset = sub_is_group(l)
			while len(rset) != 0:
				ln = rset.pop()
				prev_lines.append(ln)
				cnv.itemconfig(ln,fill=color)
			prev_lines.remove(rset)

def preline_2d(event):
	global gr_chosen, prev_lines
	if cnv.find_withtag('current') != () and not gr_chosen:
		gr_chosen = True
		l = cnv.find_withtag('current')[0]
		gr_chosen = sub_is_group(l)
		if is_group(l):
			for i in gr_chosen:
				cnv.itemconfig(i,fill='red')
		else:
			cnv.itemconfig(l,fill='red')
		mode2d_btn['state'] = 'disabled'
		prev_lines.remove(gr_chosen)

def is_group(l):
	if isinstance(sub_is_group(l),set):
		return True
	else:
		return False


def sub_is_group(l):
	for i in prev_lines:
		if isinstance(i,set):
			for j in i:
				if j == l:
					return i
	return l
		
def draw_line(line,x0,y0,x1,y1,width=1.0):
	cnv.delete(line)
	return cnv.create_line(x0,y0,x1,y1,fill=color,width=width)

def line(event):
	""" Функция для рисования прямой """
	global line_x0, line_y0, prev_lines, color, mode, cur_line, line_width, switch

	if mode == 'draw':
		cur_line = draw_line(cur_line,line_x0,line_y0,event.x,event.y,line_width)

	if mode == 'move':
		if switch == 'first' and not isinstance(cur_line,set):
			cur_line = draw_line(cur_line,event.x,event.y,cnv.coords(cur_line)[2],cnv.coords(cur_line)[3],width=1.5)

		if switch == 'second' and not isinstance(cur_line,set):
			cur_line = draw_line(cur_line,cnv.coords(cur_line)[0],cnv.coords(cur_line)[1],event.x,event.y,width=1.5)
			
		if switch == 'line':
			global m_line_x, m_line_y
			delta_x = event.x - m_line_x
			delta_y = event.y - m_line_y
			if isinstance(cur_line,set):
				gr = set()
				for i in cur_line:
					gr.add(draw_line(i,cnv.coords(i)[0]+delta_x,cnv.coords(i)[1]+delta_y,cnv.coords(i)[2]+delta_x,cnv.coords(i)[3]+delta_y,width=1.5))
				cur_line = gr
			else:
				cur_line = draw_line(cur_line,cnv.coords(cur_line)[0]+delta_x,cnv.coords(cur_line)[1]+delta_y,
								 	 cnv.coords(cur_line)[2]+delta_x,cnv.coords(cur_line)[3]+delta_y,width=1.5)
			m_line_x = event.x
			m_line_y = event.y

def after_line(event):
	if mode == 'draw':
		after_line_draw(event)
	if mode == 'move':
		after_line_move(event)
	if mode == 'group':
		after_line_group(event)

def after_line_draw(event):
	global line_x0, line_y0, prev_lines,mode, cur_line
	if isinstance(cur_line,set):
		prev_lines.append(cur_line)
	elif cnv.coords(cur_line)[1]-cnv.coords(cur_line)[0] != 0 or cnv.coords(cur_line)[3]-cnv.coords(cur_line)[2]!= 0:
		prev_lines.append(cur_line)
	a = event.y - line_y0
	b = event.x - line_x0
	c = (400 - line_y0) * b - line_x0 * a
	lbl.configure(text=str(a)+'x + '+str(-b)+'y + '+str(c)+' = 0')
	print(prev_lines)

def after_line_move(event):
	global switch, prev_lines
	switch = ''
	print(prev_lines)


def after_line_group(event):
	pass

def clear_cnv():
	global prev_lines
	prev_lines.clear()
	lbl.configure(text='Начните рисовать')
	cnv.delete(ALL)

def delete_line():
	global cur_line, line_chosen
	cnv.delete(cur_line)
	line_chosen = False
	del_btn['state'] = 'disabled'

def change_mode():
	global mode, cur_line

	if mode=='draw':
		mode = 'move'
		mode_btn.configure(text='Режим:\nПеремещение')
	else:
		mode = 'draw'
		del_btn['state'] = 'disabled'
		mode_btn.configure(text='Режим:\nРисование')
		line_chosen = False
		cnv.itemconfig(cur_line, width = 1.0)

def chose_color():
	global color
	color = colorchooser.askcolor()[1]
	print(color)

def change_width(val):
	global line_width
	line_width = int(val)/10

def group():
	global mode, prev_lines, gr
	if mode!='group':
		mode = 'group'
		g_btn.configure(text='Группировка\nON')
		mode_btn['state'] = 'disabled'
		rg_btn['state'] = 'disabled'

	else:
		mode = 'draw'
		g_btn.configure(text='Группировка\nOFF')
		mode_btn.configure(text='Режим:\nРисование')
		mode_btn['state'] = 'normal'
		rg_btn['state'] = 'normal'
		if gr != set():
			prev_lines.append(gr)
			for i in gr:
				cnv.itemconfig(i,fill=color,width=1.0)
			gr = set()

def rand16():
	a = '0123456789abcdef'
	s = '#'
	for i in range(6):
		s += a[randint(0,15)]
	return s

def rgroup():
	global mode, prev_lines
	if mode !='rgroup':
		mode = 'rgroup'
		rg_btn.configure(text='Разгруппировка\nON')
		g_btn['state'] = 'disabled'
		mode_btn['state'] = 'disabled'
		for i in prev_lines:
			if isinstance(i,set):
				c = rand16()
				for j in i:
					cnv.itemconfig(j,fill=c)
	else:
		mode = 'draw'
		rg_btn.configure(text='Разгруппировка\nOFF')
		g_btn.configure(text='Группировка\nOFF')
		mode_btn.configure(text='Режим:\nРисование')
		g_btn['state'] = 'normal'
		mode_btn['state'] = 'normal'
		
def mode_2d():
	global mode
	tl.deiconify()
	mode_btn['state'] = 'disabled'
	g_btn['state'] = 'disabled'
	rg_btn['state'] = 'disabled'
	m_btn['state'] = 'normal'
	mode = '2d'

def crt_mx():
	global matrix
	t_mx = {'t_x':0,'t_y':0,'s_x':0,'s_y':0,'r':0,'m_v':0,'m_h':0,'p_p':0,'p_q':0}
	t_mx['t_x'] = float(t_en_x.get())
	t_mx['t_y'] = float(t_en_y.get())
	t_mx['s_x'] = float(s_en_x.get())
	t_mx['s_y'] = float(s_en_y.get())
	t_mx['r'] = float(r_en.get())
	t_mx['m_v'] = float(m_en_v.get())
	t_mx['m_h'] = float(m_en_h.get())
	t_mx['p_p'] = float(p_en_p.get())
	t_mx['p_q'] = float(p_en_q.get())
	matrix = [[1,0,0],[0,1,0],[t_mx['t_x'],t_mx['t_y'],1]]
	matrix = np.matmul(matrix,[[t_mx['s_x'],0,0],[0,t_mx['s_y'],0],[0,0,1]])
	matrix = np.matmul(matrix,[[math.cos(t_mx['r']),math.sin(t_mx['r']),0],
							   [-math.sin(t_mx['r']),math.cos(t_mx['r']),0],
							   [0,0,1]])
	matrix = np.matmul(matrix,[[t_mx['m_v'],0,0],[0,t_mx['m_h'],0],[0,0,1]])
	matrix = np.matmul(matrix,[[1,0,0],[0,1,0],[t_mx['p_p'],t_mx['p_q'],1]])
	apl_btn['state'] = 'normal'

def apl_mx():
	global gr_chosen, matrix, prev_lines, mode
	if gr_chosen:
		if not isinstance(gr_chosen,set):
			s = set()
			s.add(gr_chosen)
			gr_chosen = s

		pnt_mx = []
		for i in gr_chosen:
			coords = cnv.coords(i)
			pnt_mx.append([coords[0],coords[1],1])
			pnt_mx.append([coords[2],coords[3],1])
			cnv.delete(i)
		pnt_mx = np.matmul(pnt_mx,matrix)
		# нормализация
		gr_chosen.clear()
		for i in range(0,len(pnt_mx),2):
			gr_chosen.add(cnv.create_line(pnt_mx[i][0],pnt_mx[i][1],pnt_mx[i+1][0],pnt_mx[i+1][1]))
		if len(gr_chosen) != 1:
			prev_lines.append(gr_chosen)
		else:
			prev_lines.append(gr_chosen.pop())
		gr_chosen = False
		mode2d_btn['state'] = 'normal'
		mode_btn['state'] = 'normal'
		mode_btn.configure(text='Режим:\nРисование')
		g_btn['state'] = 'normal'
		rg_btn['state'] = 'normal'
		m_btn['state'] = 'disabled'
		apl_btn['state'] = 'disabled'
		mode = 'draw'



# Создание главного окна приложения
root = Tk()
root.title('Графический редактор Истомин АСУ-18')
root.resizable(False, False)
root['bg']='grey'

tl = Toplevel(root)
tl.withdraw()

main_menu = Menu(root)
root.config(menu=main_menu)
mode_menu = Menu(main_menu,tearoff=0)
main_menu.add_cascade(label='Режимы работы',menu=mode_menu)
mode_menu.add_command(label='Рисование/Перемещение/Группировка')
mode_menu.add_command(label='2D операции',command=mode_2d)


# Создание поля для рисования
cnv = Canvas(root, width=400, height=300)
prev_lines.append(cnv.create_line(100,100,200,200))
cnv.bind('<1>',preline)
cnv.bind('<B1-Motion>',line,'+')
cnv.bind('<B1-ButtonRelease>',after_line,'+')
cnv.grid(row=1, rowspan=10, column=1, columnspan=8, padx=2, pady=2)

# Создание поля для уравнения прямой
lbl = Label(root, text='Начните рисовать')
lbl.grid(row=11, rowspan=2, column=1, columnspan=1, padx=2, pady=2)

# Кнопка для очистки рабочей области
clr_btn = Button(text='Очистить', command=clear_cnv,width=15)
clr_btn.grid(row=1, rowspan=1, column=9, columnspan=1, padx=2, pady=2)

# Кнопка для удаления прямой
del_btn = Button(text='Удалить прямую', command=delete_line,width=15)
del_btn['state'] = 'disabled'
del_btn.grid(row=2, rowspan=1, column=9, columnspan=1, padx=2, pady=2)

# Кнопка режима работы
mode_btn = Button(text='Режим:\nРисование', command=change_mode,width=15,height=2)
mode_btn.grid(row=3, rowspan=1, column=9, columnspan=1, padx=2, pady=2)

#Кнопка выбора цвета
col_btn = Button(text='Выбор цвета', command=chose_color,width=15)
col_btn.grid(row=4, rowspan=1, column=9, columnspan=1, padx=2, pady=2)

# Выбор толщины
w_lbl=Label(text='Выбор толщины',width=15)
w_lbl.grid(row=5,rowspan=1,column=9,columnspan=1,padx=2,pady=2)
scale = Scale(root,orient=HORIZONTAL,from_=10,to=20,command=change_width)
scale.grid(row=6,rowspan=1,column=9,columnspan=1,padx=2,pady=2)

# Группировка
g_btn = Button(text='Группировка\nOFF',command=group,width=15)
g_btn.grid(row=7,rowspan=1,column=9,columnspan=1,padx=2,pady=2)

# Разгруппировка
rg_btn = Button(text='Разгруппировка\nOFF',command=rgroup,width=15)
rg_btn.grid(row=8,rowspan=1,column=9,columnspan=1,padx=2,pady=2)

# Блок 2Д операций
# Кнопка перехода в 2Д операции
mode2d_btn = Button(tl,text='Выбрать фигуру',command=mode_2d)
mode2d_btn.grid(row=1,rowspan=1,column=6,columnspan=3,padx=2,pady=2)
# Смещение
t_lbl = Label(tl,text='Сместить на x,y',bg='grey')
t_lbl.grid(row=2,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
t_en_x = Entry(tl,width=4)
t_en_x.insert(0,0)
t_en_x.grid(row=2,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
t_en_y = Entry(tl,width=4)
t_en_y.insert(0,0)
t_en_y.grid(row=2,rowspan=1,column=8,columnspan=1,padx=2,pady=2)
# Масштабирование
s_lbl = Label(tl,text='Масштабировать в по x,y',bg='grey')
s_lbl.grid(row=3,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
s_en_x = Entry(tl,width=4)
s_en_x.insert(0,1)
s_en_x.grid(row=3,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
s_en_y = Entry(tl,width=4)
s_en_y.insert(0,1)
s_en_y.grid(row=3,rowspan=1,column=8,columnspan=1,padx=2,pady=2)
# Вращение
r_lbl = Label(tl,text='Вращать на',bg='grey')
r_lbl.grid(row=4,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
r_en = Entry(tl,width=4)
r_en.insert(0,0)
r_en.grid(row=4,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
# Зеркалирование
m_lbl = Label(tl,text='Зеркалировать |-',bg='grey')
m_lbl.grid(row=5,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
m_en_v = Entry(tl,width=4)
m_en_v.insert(0,1)
m_en_v.grid(row=5,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
m_en_h = Entry(tl,width=4)
m_en_h.insert(0,1)
m_en_h.grid(row=5,rowspan=1,column=8,columnspan=1,padx=2,pady=2)
# Проецирование
p_lbl = Label(tl,text='Проецировать на',bg='grey')
p_lbl.grid(row=6,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
p_en_p = Entry(tl,width=4)
p_en_p.insert(0,0)
p_en_p.grid(row=6,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
p_en_q = Entry(tl,width=4)
p_en_q.insert(0,0)
p_en_q.grid(row=6,rowspan=1,column=8,columnspan=1,padx=2,pady=2)
# Кнопка формирования данных для матрицы
m_btn = Button(tl,text='Сформировать матрицу',command=crt_mx)
m_btn['state'] = 'disabled'
m_btn.grid(row=7,rowspan=1,column=6,columnspan=1,padx=2,pady=2)
# Применение матрицы к выбранной группе
apl_btn = Button(tl,text='Применить матрицу',command=apl_mx)
apl_btn['state'] = 'disabled'
apl_btn.grid(row=7,rowspan=1,column=7,columnspan=1,padx=2,pady=2)
# Запуск главного цикла приложения
root.mainloop()

