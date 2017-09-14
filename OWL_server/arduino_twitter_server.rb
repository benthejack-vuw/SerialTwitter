require 'serialport'
require 'twitter'
require_relative 'TwitterConfig'
require_relative 'OWL'


class SerialTwitter

	def initialize
		@serial           = false
		@rest_client      = Twitter::REST::Client.new TwitterConfig.config_data
		@streaming_client = Twitter::Streaming::Client.new TwitterConfig.config_data
		@owl = OWL.new self
		@owl.run
	end

	def println args
		puts "#{args[0]}"
	end

	def log args
		print args[0].chomp
	end

	def number_of_tweets_with args
		puts "searching for number of tweets with: #{args[0]}"
	    numTweets = @rest_client.search(args[0], result_type: "recent").count
		puts "number of tweets found with #{args[0]}: #{numTweets}"
		@owl.write "number_of_tweets_with", numTweets
	end

	def latest_tweet_with args
		puts "searching for tweet with: #{args[0]}"
			tweet = @rest_client.search(args[0], result_type: "recent").last
		puts "latest tweet with #{args[0]}: #{tweet.text}"
		@owl.write "latest_tweet_with", tweet.text
	end

	def watch_for_tweets_with args
    puts "server is watching for tweets containing '#{args[0]}', all other tasks will now be blocked"

		@streaming_client.filter(track: args[0]) do |tweet|
      puts tweet.text
			@owl.write "watch_for_tweets_with", tweet.text;
		end

	end

	def number_of_likes args

	end

	def number_of_retweets args
	end

	def number_of_friends args
	end

	def post_tweet args
		text = args[0].chomp
		puts "tweeting: #{text}"
		@rest_client.update(text);
	end

	def send_to_arduino value

	end

end

twitter = SerialTwitter.new
