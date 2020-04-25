        d = []
        if self.rect.midtop[1] < other.rect.midtop[1]:
            d.append("top")
        if self.rect.midleft[0] < other.rect.midleft[0]:
            d.append("left")
        if self.rect.midright[0] > other.rect.midright[0]:
            d.append("right")
        if self.rect.midbottom[1] > other.rect.midbottom[1]:
            d.append("bottom")