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