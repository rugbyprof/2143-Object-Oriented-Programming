class Config:
    #no constructor
    width = 1024
    height = 768
    sprite_images = {
        "blue" : "./images/pac_blue_30x30.png",
        "light_blue" : "./images/pac_light_blue_30x30.png",
        "red" : "./images/pac_red_30x30.png",
        "white" : "./images/pac_white_30x30.png",
        "yellow" : "./images/pac_yellow_30x30.png",
        "orange" : "./images/pac_orange_30x30.png",
        "green" : "./images/pac_green_30x30.png"
    }
    social_distancing = False
    infection_radius = 10
    infection_rate = .20


if __name__=='__main__':
    print("I'm testing config!")