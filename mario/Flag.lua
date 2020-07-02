Flag = Class{}

function Flag:init(map)

    self.map = map
    self.x = map.tileWidth * (map.mapWidth - 2)
    self.y = map.tileHeight * (map.mapHeight / 2 - 9)
    self.xOffset = 6

    self.texture = love.graphics.newImage('graphics/spritesheet.png')
    self.sprites = generateQuads(self.texture, 16, 16)
    self.frames = {}

    self.currentFrame = nil

    self.animation = Animation ({
        texture = self.texture,
        frames = {
            self.sprites[13], self.sprites[14], self.sprites[15]
        },
        interval = 0.2
    })

end

function Flag:update(dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()
end

function Flag:render()
    love.graphics.draw(self.texture, self.currentFrame, self.x - self.xOffset, self.y)
end