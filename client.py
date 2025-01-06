import io
import socket
import struct
import time
import cv2
import serial
# Setup serial connection to Arduino
serial_port = '/dev/ttyACM0' #'/dev/ttyACM0'
host = '192.168.0.111'
#arduino_serial = serial.Serial(serial_port, 115200, timeout=1)
# Network setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, 8000))
connection = client_socket.makefile('wb')
# Create a separate socket for receiving commands
command_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
command_socket.connect((host, 8001)) # Different port for commands
command_recv = command_socket.makefile('rb')
# cv2.CAP_V4L2
try:
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    if not cap.isOpened():
        print("Error: Could not open video device")
        exit(1)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320) # Set width
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240) # Set height
    cap.set(cv2.CAP_PROP_FPS, 15)
    time.sleep(2)
    start = time.time()
    stream = io.BytesIO()
    # Separate thread or process would be better for real-world use
    import threading
    def receive_commands():
        while True:
            try:
                command =
                command_recv.readline().decode('utf-8').strip()
                if command != 'x':
                    print(f"Received command: {command}")
                # arduino_serial.write(command.encode())
            except Exception as e:
            print(f"Error receiving command: {e}")
            break
    # Start command receiving in a thread
    command_thread = threading.Thread(target=receive_commands)
    command_thread.daemon = True
    command_thread.start()
    while True:
        ret, frame = cap.read() # Capture a frame from the webcam
        if not ret:
            print("Failed to grab frame")
            break
        # Encode the frame as JPEG
        ret, jpg = cv2.imencode('.jpg', frame)
        if not ret:
            print("Failed to encode image")
            break
        # Send the JPEG image over the network
        connection.write(struct.pack('<L', len(jpg)) ) # Send
        length of the image
        connection.flush()
        connection.write(jpg.tobytes()) # Send the actual image
    # if time.time() - start > 600: # Run for 10 minutes (600
    # seconds)
# break
# Send the end of stream signal (0 length)
    connection.write(struct.pack('<L', 0))
finally:
connection.close()
client_socket.close()
command_socket.close()
arduino_serial.close()