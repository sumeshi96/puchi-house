import discord
import discord_token
import puchi_camera as pc

intents = discord.Intents.all()
intents.messages = True
intents.message_content = True
client = discord.Client(intents=intents)


@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')


@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if message.content.startswith('?puchi'):
        pc.get_img()
        await message.channel.send(file=discord.File('./image.jpg'))

client.run(discord_token.get_token())
