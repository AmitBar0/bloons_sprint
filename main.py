import serial

BAUDRATE = 9600
PORT = 'com7'


class DummyRobot:
    def arduino_write(self, s: str):
        print(f'writing: "{s}"')

    def arduino_read(self):
        output = 'output'
        print('reading:', output)
        return output


class Robot:
    def __init__(self):
        self.arduino = serial.Serial(PORT, BAUDRATE)

    def arduino_write(self, s: str):
        print(f'writing: "{s}"')
        self.arduino.write(s.encode(encoding='utf-8'))

    def arduino_read(self):
        output = str(self.arduino.readline())
        print('reading:', output)
        return output


def dummy(robot):
    while True:
        command = input('Enter command: ')
        robot.arduino_write(command)
        print(robot.arduino_read())


def main(robot):
    import pygame
    import sys

    # Initialize Pygame
    pygame.init()

    # Set up the screen
    SCREEN_WIDTH = 400
    SCREEN_HEIGHT = 300
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Arrow Key Presses")

    # Define colors
    WHITE = (255, 255, 255)

    # Set up the clock
    clock = pygame.time.Clock()

    # Main loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    robot.arduino_write("1")
                elif event.key == pygame.K_RIGHT:
                    robot.arduino_write("0")
                elif event.key == pygame.K_UP:
                    robot.arduino_write("2")
                elif event.key == pygame.K_DOWN:
                    robot.arduino_write("3")
            elif event.type == pygame.KEYUP:
                if event.key in [pygame.K_LEFT, pygame.K_RIGHT, pygame.K_UP, pygame.K_DOWN]:
                    robot.arduino_write("4")

        # Fill the background with white
        screen.fill(WHITE)

        # Update the display
        pygame.display.flip()

        # Cap the frame rate
        clock.tick(60)

    # Quit Pygame
    pygame.quit()
    sys.exit()


if __name__ == '__main__':
    robot = Robot()
    main(robot)
