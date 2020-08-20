import tkinter as tk
buttonList=[]
def deseneazaHarta(master):
    frameLengh=600
    frameHeigh=400
    global tablaDeJoc
    tablaDeJoc=tk.Frame(master=master,bg="white")
    tablaDeJoc.place(x=100,y=100,width=frameLengh,heigh=frameHeigh)
def deseneazaButoane(master):
    buttonWidth=60
    buttonHeigh=40
    for x in range (0,600,buttonWidth):
        for y in range(0,400,buttonHeigh):
            button=tk.Button(master=master,bg="green")
            button.place(x=x,y=y,width=buttonWidth,heigh=buttonHeigh)
            buttonList.append(button)
def addQuitButton():
    quitButton=tk.Button(text="QUIT",master=root,command=quit)
    quitButton.place(width=50,heigh=30,x=700,y=550)

root=tk.Tk()
rootLengh=800
rootHeigh=600
root.title("Game")
root.geometry(str(rootLengh)+"x"+str(rootHeigh)+"+0+0")
deseneazaHarta(root)
deseneazaButoane(tablaDeJoc)
addQuitButton()
root.mainloop()
