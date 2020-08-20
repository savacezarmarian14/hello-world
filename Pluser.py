import tkinter as tk
import random
import time



def setRoot(width,heigh,xPos,yPos):
    root.geometry("{}x{}+{}+{}".format(width,heigh,xPos,yPos))
def setPlayground(width,heigh):
    global pg
    pg=tk.Frame(root,bg="gray")
    pg.place(width=width,heigh=heigh,x=50,y=50)
def setQuitButton():
    q=tk.Button(root,text="QUIT",command=quit)
    q.place(width=100,heigh=30,x=250,y=560)
def setPlayerScore():
    global scoreText, score , scoreLabel
    scoreLabel=tk.Label(root)
    score=0
    scoreText = "Score : {}                                                                         Player: {}"
    scoreLabel.place(x=50,y=0)
    scoreLabel.configure(text=scoreText.format(score,"Cezar Sava"),font=100)
def setButtons():
    global buttonsMatrix
    global buttonsMatrixNUM
    buttonWidth=50
    buttonHeigh=50
    buttonsMatrix=[[0 for x in range(10)] for y in range(10)]
    buttonsMatrixNUM=[[0 for x in range(10)] for y in range(10)]
    for y in range (0,500,buttonHeigh):
        i=y//buttonWidth
        for x in range (0,500,buttonWidth):
            j=x//buttonHeigh
            buttonsMatrix[i][j]=tk.Button(pg,text=str(i)+"x"+str(j),activebackground="green",bg="white")
            buttonsMatrix[i][j].place(width=buttonWidth,heigh=buttonHeigh,x=x,y=y)
            pg.update()
            print(str(i)+"x"+str(j))
            buttonsMatrix[i][j].bind('<Button-1>',buttonClick)

def setButtonsMatrix():
    for i in range(10):
        for j in range(10):
            num=random.randint(1,3)*2
            if buttonsMatrixNUM[i][j]==0:
                buttonsMatrixNUM[i][j]=num
            buttonsMatrix[i][j].configure(bg="white")
def setButtonsText():
    for i in range(10):
        for j in range(10):
            buttonsMatrix[i][j].configure(text=str(buttonsMatrixNUM[i][j]))
def buttonClick(event):
    x = event.x_root - pg.winfo_rootx()
    y = event.y_root - pg.winfo_rooty()
    x-=x%50
    y-=y%50
    j=x//50
    i=y//50
    fill(i,j)
    buttonsMatrix[i][j].update()
    time.sleep(1/4)
    buttonsMatrixNUM[i][j]=makeSum()
    updateScore(buttonsMatrixNUM[i][j])
    printMatrix(buttonsMatrixNUM)
    setButtonsMatrix()
    setButtonsText()


def updateScore(scor):
    global score
    score+=scor
    scoreLabel.configure(text=scoreText.format(score,"Cezar Sava"),font=100)


def fill(i,j):
    d1=[0,0,1,-1]
    d2=[1,-1,0,0]
    buttonsMatrixNUM[i][j] *= (-1)
    buttonsMatrix[i][j].configure(bg="green")
    print((i,j))
    for ii in range(4):
        if (i+d1[ii]) in range (10) and (j+d2[ii]) in range(10):
            if (-1*buttonsMatrixNUM[i+d1[ii]][j+d2[ii]]) == buttonsMatrixNUM[i][j] and buttonsMatrixNUM[i+d1[ii]][j+d2[ii]] > 0 :
                fill(i+d1[ii],j+d2[ii])

def printMatrix(matrix):
    for i in range(10):
        print(matrix[i])
def makeSum():
    sum=0
    for i in range(10):
        for j in range(10):
            if buttonsMatrixNUM[i][j] < 0 :
                sum-=buttonsMatrixNUM[i][j]
                buttonsMatrixNUM[i][j]=0
    return sum


root=tk.Tk()

setRoot(600,600,0,0)
setPlayground(500,500)
setQuitButton()
setPlayerScore()
setButtons()
setButtonsMatrix()
setButtonsText()

root.mainloop()