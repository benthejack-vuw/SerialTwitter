require 'serialport'
require 'twitter'

class SerialTwitter

	def initialize
		@serial = false
		@client = Twitter::REST::Client.new do |config|
		  config.consumer_key        = "4q2s46X0OGlxTfxV0XhzsF8Fc"
		  config.consumer_secret     = "8LBoCYQNJ5rXqj9zXGSNT18tUZXvi1uqcbV0NdFw3vvfCa3uJF"
		  config.access_token        = "47606826-1iSZHkVFMnL9xtcV7Hs3XgRo0tfF1Uj3tT4xtZpnx"
		  config.access_token_secret = "oslNQVT3F4ZBDiu4N5ZudZi6IgTIrxYB4jJU3P8tvQYlu"
		end

		@discard = ["/dev/tty.Bluetooth-Incoming-Port",
					      "/dev/cu.Bluetooth-Incoming-Port" ]
	end

	def connect baudrate
		baud_rate = baudrate
		data_bits = 8
		stop_bits = 1
		parity = SerialPort::NONE

		while(!@serial) do
			handshake = 0
			ports = Dir.glob("/dev/{tty,cu}.*") - @discard
			ports.each do |p|
				puts p
				serial = SerialPort.new(p, baud_rate, data_bits, stop_bits, parity)
				sleep 3

				while(!serial.eof && !@serial) do
					handshake = serial.readline.chomp
					if handshake == "arduino"
						@serial = serial #ASCII 'C'
						@serial.write "arduinoServer\n"
						puts "CONNECTED TO ARDUINO"
					end
				end

				break if(@serial)
			end
		end

	end

	def update
		command = @serial.readline
		puts "command - #{command}"

		args = command.split(":")
		message = args.shift()

		self.send message, args
	end

	def tweets_with args
	  numTweets = @client.search(args[0], result_type: "recent").count
		puts numTweets
		@serial.write(numTweets)
	end

	def number_of_likes username

	end

	def number_of_retweets username

	end

	def number_of_friends username

	end

	def post_tweet text

	end

	def send_to_arduino value

	end

end


s = SerialTwitter.new
s.connect 9600
while true do
	s.update
end
