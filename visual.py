import pygame
import imageio
import time
import os

CELL_SIZE = 20
FRAME_DELAY = 0.1  # seconds per frame
FPS = int(1 / FRAME_DELAY)

COLORS = {
    '0': (30, 30, 30),      # Empty
    '1': (0, 255, 0),       # Snake
    '2': (255, 0, 0),       # Apple
}

def load_frames(filename):
    with open(filename, 'r') as f:
        raw = f.read()
    frames = raw.strip().split("===\n")
    return [frame.strip().splitlines() for frame in frames]

def draw_frame(screen, frame):
    screen.fill((0, 0, 0))
    for y, row in enumerate(frame):
        for x, cell in enumerate(row):
            color = COLORS.get(cell, (255, 255, 255))
            pygame.draw.rect(screen, color, (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))
    pygame.display.flip()

def main():
    frames = load_frames("max.txt")
    if not frames:
        print("No frames found!")
        return

    rows, cols = len(frames[0]), len(frames[0][0])
    pygame.init()
    screen = pygame.display.set_mode((cols * CELL_SIZE, rows * CELL_SIZE))
    pygame.display.set_caption("Snake Replay")

    clock = pygame.time.Clock()

    # Create temp folder to save screenshots
    os.makedirs("temp_frames", exist_ok=True)
    saved_images = []

    frame_num = 0
    running = True
    while running and frame_num < len(frames):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        draw_frame(screen, frames[frame_num])

        # Save current frame
        filename = f"temp_frames/frame_{frame_num:04d}.png"
        pygame.image.save(screen, filename)
        saved_images.append(filename)

        frame_num += 1
        clock.tick(FPS)

    # After frames played
    print("Playback finished. Press any key to exit.")
    
    waiting = True
    while waiting:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN or event.type == pygame.QUIT:
                waiting = False

    # Save MP4
    print("Saving video...")
    images = [imageio.v2.imread(img) for img in saved_images]
    imageio.mimsave('replay.mp4', images, fps=FPS)
    print("Saved as replay.mp4")

    # Clean up temp frames
    for img in saved_images:
        os.remove(img)
    os.rmdir("temp_frames")

    pygame.quit()

if __name__ == "__main__":
    main()