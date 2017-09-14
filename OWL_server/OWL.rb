class OWL
  ARDUINO_CONNECTION_DELAY = 4
  DISCARD_PORTS = ["/dev/tty.Bluetooth-Incoming-Port",
							     "/dev/cu.Bluetooth-Incoming-Port" ]

  def initialize delegate, baud_rate = 9600
    @baud_rate = baud_rate
    @delegate = delegate
    @data_bits = 8
    @stop_bits = 1
    @parity = SerialPort::NONE
    @serial = nil
    connect
  end

  def connect
    block_loop do
      ports = Dir.glob("/dev/{tty,cu}.*") - DISCARD_PORTS
      ports.each{ | p | attempt_connection p; break if @serial }
      ( @serial != nil )
   	 end
	end

  def write command, message
    @serial.write "#{command}~#{message}|"
  end

  def run
    block_loop do
      command = @serial.readline.chomp "|\r\n"
      args = command.split("~")
      message = args.shift()
      ( @delegate.respond_to?( message ) ) ? @delegate.send( message, args ) : puts( "'#{message}' is not implemented in #{@delegate.class.name}" )
      false # run forever
    end
  end

  private

  def block_loop
    begin
      conditional = yield if block_given?
    end until conditional
  end

  def attempt_connection p
		puts "trying to connect to:#{p}"
		conn = SerialPort.new(p, @baud_rate, @data_bits, @stop_bits, @parity)
		sleep ARDUINO_CONNECTION_DELAY
    block_loop do
      attempt_handshake conn
    end
  end

  def attempt_handshake conn
    handshake = conn.readline.chomp
		if handshake == "arduino"
			@serial = conn
			@serial.write "arduinoServer"
			@serial.flush_input
			puts "CONNECTED TO ARDUINO"
		end
    (@serial != nil)
  end

end
