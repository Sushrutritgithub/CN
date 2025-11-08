import time 
import random 
 
# Leaky Bucket class 
class LeakyBucket: 
    def __init__(self, bucket_size, output_rate): 
        """ 
        :param bucket_size: Maximum capacity of the bucket (in packets) 
        :param output_rate: Number of packets sent per second 
        """ 
        self.bucket_size = bucket_size 
        self.output_rate = output_rate 
        self.current_size = 0  # Current packets in bucket 
 
    def add_packet(self, packet_size): 
        """Add incoming packets to the bucket""" 
        if self.current_size + packet_size > self.bucket_size: 
            print(f"Bucket overflow! Packet of size {packet_size} dropped.") 
        else: 
            self.current_size += packet_size 
            print(f"Packet of size {packet_size} added. Current bucket size: {self.current_size}") 
 
    def leak(self): 
        """Send packets (leak) at a constant rate""" 
        if self.current_size == 0: 
            print("Bucket is empty. Nothing to send.") 
        else: 
            leak_amount = min(self.output_rate, self.current_size) 
            self.current_size -= leak_amount 
            print(f"Leaked {leak_amount} packets. Remaining: {self.current_size}") 
 
# Simulation 
def simulate_leaky_bucket(): 
    bucket_size = int(input("Enter bucket size (packets): ")) 
    output_rate = int(input("Enter output rate (packets/sec): ")) 
 
    bucket = LeakyBucket(bucket_size, output_rate) 
 
    # Simulate random incoming packets 
    for t in range(1, 11): 
        print(f"\nTime {t}:") 
        incoming = random.randint(0, 10) 
        print(f"Incoming packets: {incoming}") 
        bucket.add_packet(incoming) 
 
        # Leak packets each second 
        bucket.leak() 
        time.sleep(1)  # simulate time passing 
 
if __name__ == "__main__": 
    simulate_leaky_bucket() 