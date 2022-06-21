import pygame
from pygame.locals import *
import game
import constants as c
import os

class main_screen:
    def __init__(self):
        self.pvp_img = pygame.transform.scale(pygame.image.load(os.path.join("Assets", "pvp.png")), (c.BOARD_ALT_WIDTH, c.BOARD_ALT_HEIGHT/2))
        self.ai_img = pygame.transform.scale(pygame.image.load(os.path.join("Assets", "ai.png")), (c.BOARD_ALT_WIDTH, c.BOARD_ALT_HEIGHT/2))
        self.win = pygame.display.set_mode((c.BOARD_ALT_WIDTH, c.BOARD_ALT_HEIGHT))
        self.clientg = game.game(self.win)
        self.pvp_hover = False
        self.ai_hover = False
        self.pvp_rect = (0,0,c.BOARD_ALT_WIDTH, c.BOARD_ALT_HEIGHT/2)
        self.ai_rect = (0, c.BOARD_ALT_HEIGHT/2,c.BOARD_ALT_WIDTH, c.BOARD_ALT_HEIGHT/2)
        self.font = pygame.font.SysFont("Arial", 30)
        self.to_choose = False
        self.choose_txt = self.font.render("choose color!", True, (255, 255, 255))
        self.black_txt = self.font.render("black", True, (255, 255, 255))
        self.white_txt = self.font.render("white", True, (255, 255, 255))
        self.black_txt_hitbox = (c.BOARD_ALT_WIDTH/2 - 40, c.BOARD_ALT_HEIGHT/2 - 100, 50, 30)
        self.white_txt_hitbox = (c.BOARD_ALT_WIDTH/2 + 40, c.BOARD_ALT_HEIGHT/2 - 100, 50, 30)


    def redraw(self, win):
        win.blit(self.pvp_img, (0,0))
        win.blit(self.ai_img, (0, c.BOARD_ALT_HEIGHT/2))
        if self.pvp_hover:
            pygame.draw.rect(win, [255,255,255], self.pvp_rect, 5)
        if self.ai_hover:
            pygame.draw.rect(win, [255,255,255], self.ai_rect, 5)
        if self.to_choose:
            win.blit(self.choose_txt, (c.BOARD_ALT_WIDTH/2 - 30, c.BOARD_ALT_HEIGHT/2))
            win.blit(self.black_txt, (c.BOARD_ALT_WIDTH/2 - 70, c.BOARD_ALT_HEIGHT/2 - 100))
            win.blit(self.white_txt, (c.BOARD_ALT_WIDTH/2 + 10, c.BOARD_ALT_HEIGHT/2 - 100))
        pygame.display.update()


    def intersects(self, rect, pos):
        if pos[0] >= rect[0] and pos[0] <= rect[2] and pos[1] >= rect[1] and pos[1] <= rect[3]:
            return True
        return False


    def start(self):
        run = True
        clock = pygame.time.Clock()
        while run:
            clock.tick(30)

            self.redraw(self.win)

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                    quit()
                    pygame.quit()

                if event.type == pygame.MOUSEMOTION:
                    if not self.to_choose:
                        pos = pygame.mouse.get_pos()
                        if self.intersects(self.pvp_rect, pos):
                            self.pvp_hover = True
                        else:
                            self.pvp_hover = False
                        pos = pygame.mouse.get_pos()
                        if self.intersects(self.ai_rect, pos):
                            self.ai_hover = True
                        else:
                            self.ai_hover = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    pos = pygame.mouse.get_pos()
                    if not self.to_choose:
                        if self.intersects(self.pvp_rect, pos):
                            self.clientg.startAI("w")
                        if self.intersects(self.ai_rect, pos):
                            self.to_choose = True
                    else:
                        if self.intersects(self.white_txt_hitbox, pos):
                            self.clientg.startAI("w")
                        if self.intersects(self.black_txt_hitbox, pos):
                            self.clientg.startAI("b")
                        self.to_choose = False



















'''


                        import socket

my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
my_socket.connect(("127.0.0.1", 5555))
msg = "hello"
while True:
    my_socket.send(msg.encode())
    data = my_socket.recv(1024).decode()
    print("THE SERVER SENT: " + data)
    if (data == "BYE!!!" or data == "KILL SERVER!!!"):
        break
    msg = input("Please enter your message\n")


my_socket.close()


'''






'''







import socket
import like_a_rolling_project.chatlib_skeleton as ch #  To use chatlib functions or consts, use chatlib.****

SERVER_IP = "127.0.0.1"  # Our server will run on same computer as client
SERVER_PORT = 5678

# HELPER SOCKET METHODS

def build_and_send_message(conn, code, data):
    msg = str(ch.build_message(code, data))
    nmsg = str(msg).encode()
    conn.send(nmsg)
"""
	Builds a new message using chatlib, wanted code and message. 
	Prints debug info, then sends it to the given socket.
	Paramaters: conn (socket object), code (str), data (str)
	Returns: Nothing
"""
# Implement Code


def recv_message_and_parse(conn):
    full_msg = conn.recv(ch.MAX_MSG_LENGTH).decode()
    cmd, data = ch.parse_message(full_msg)
    return cmd, data
"""
Recieves a new message from given socket,
then parses the message using chatlib.
Paramaters: conn (socket object)
Returns: cmd (str) and data (str) of the received message. 
If error occured, will return None, None
"""

def build_send_recv_parse(conn, code, data):
    build_and_send_message(conn, code, data)
    (msg_code, msg) = recv_message_and_parse(conn)
    return msg_code, msg

def get_score(conn):
    code, msg = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["get_score"],"")
    if(code == "ERROR"):
        print("ERROR")
    else:
        print(msg)

def get_highscore(conn):
    code, msg = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["get_score_table"], "")
    if(code == "ERROR"):
        print("ERROR")
    else:
        print("Your score: " + msg)

def menu():
    print("\nq\tQuit\ns\tScore\n"
          "h\tHigh Score\np\tPlay Question\nl\tGet all logged users\n")
    option = input("Please choose an option: ")
    return option

def play_question(conn):
    while True:
        code, msg = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["get_question"], "")
        if code == "ERROR":
            print("ERROR with getting the question")
        if code == "NO_QUESTIONS":
            print("No more questions\n Game Over\n")
        question_info = ch.split_data(msg, 6)
        id = question_info[0]
        question = question_info[1]
        answers = question_info[2:6]
        print("Q: " + question + "\n")
        for i in range(4):
            print("\t" + str(i+1) + ": " + answers[i])
        ans = input("Please choose an answer [1-4]: ")
        answer_to_send = ch.join_data((id, str(ans)))
        code, msg = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["send_answer"], answer_to_send)
        if code == "ERROR":
            print("ERROR with getting the right answer")
        if code == "CORRECT_ANSWER":
            print("Yes!!!")
        if code == "WRONG_ANSWER":
            print("wrong :(\nThe correct answer is: " + msg)
        if(input("Would you like to continue\ny/n\n") == "n"):
            break


def get_logged_users(conn):
    code, msg = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["get_logged_users"], "")
    if code == "ERROR":
        print("ERROR with getting the logged users")
    else:
        print(msg)

def connect():
    # Implement Code
    my_socket = socket.socket()
    my_socket.connect((SERVER_IP, SERVER_PORT))
    pass
    return my_socket


def error_and_exit(error_msg):
    # Implement code
    print(error_msg)
    exit()
    pass

def encrypt(password):
    return password

def login(conn):
    while True:
        username = input("Please enter username: \n")
        password = input("Please enter password: \n")
        data = ch.join_data((username,encrypt(password)))

        code, data = build_send_recv_parse(conn, ch.PROTOCOL_CLIENT["login_msg"], data)
        if code == "ERROR":
            print("login unsuccessful")
        else:
            print("logged in!")
            return


    pass

def logout(conn):
    build_and_send_message(conn, ch.PROTOCOL_CLIENT["logout_msg"], "")
    print("Goodbye!")
    pass

def main():
    conn = connect()
    login(conn)
    while True:
        op = menu()
        if(op == "s"):
            get_score(conn)
        if(op == "q"):
            logout(conn)
            break
        if(op == "h"):
            get_highscore(conn)
        if op == "p":
            play_question(conn)
        if op == "l":
            get_logged_users(conn)
    conn.close()
    exit()
    pass

if __name__ == '__main__':
    main()
'''