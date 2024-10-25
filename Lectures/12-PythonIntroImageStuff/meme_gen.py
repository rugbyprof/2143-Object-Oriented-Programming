from PIL import Image, ImageDraw, ImageFont

class MemeGenerator:
    def __init__(self, image_path, top_text, bottom_text):
        self.image_path = image_path
        self.top_text = top_text
        self.bottom_text = bottom_text
        self.image = Image.open(self.image_path)
        self.draw = ImageDraw.Draw(self.image)
        self.width, self.height = self.image.size
        self.font_size = int(self.height / 10)
        self.font = ImageFont.truetype("arial.ttf", self.font_size)

    def generate_meme(self):
        # Draw top text
        top_text_width, top_text_height = self.draw.textsize(self.top_text, font=self.font)
        x = (self.width - top_text_width) / 2
        y = self.height * 0.05
        self.draw.text((x, y), self.top_text, font=self.font, fill=self.get_text_color())

        # Draw bottom text
        bottom_text_width, bottom_text_height = self.draw.textsize(self.bottom_text, font=self.font)
        x = (self.width - bottom_text_width) / 2
        y = self.height * 0.85 - bottom_text_height
        self.draw.text((x, y), self.bottom_text, font=self.font, fill=self.get_text_color())

        # Save the meme
        self.image.save("meme.png")

    def get_text_color(self):
        # Get the average color of the image
        colors = self.image.getcolors(self.width * self.height)
        avg_color = sum([c[0] * c[1][0] for c in colors]) / sum([c[0] for c in colors])

        # Choose black or white text depending on the brightness of the image
        if avg_color > 128:
            return (0, 0, 0)  # black
        else:
            return (255, 255, 255)  # white
        
        
if __name__=='__main__':
    mg = MemeGenerator('./memes/Disaster-Girl.jpg', "hello", "goodbye")
    mg.generate_meme()