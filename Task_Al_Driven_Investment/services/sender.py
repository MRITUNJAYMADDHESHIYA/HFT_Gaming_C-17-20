import pywhatkit
from datetime import datetime


class MessageSender:

    def send(self, record):

        try:

            mobile = "+91" + str(record.mobile)   # convert to string + add India code

            print(f"Sending WhatsApp message to {mobile}")

            now = datetime.now()

            ###########
            #  send message 1 minute later
            hour = now.hour
            minute = now.minute + 1

            pywhatkit.sendwhatmsg(
                mobile,
                record.message,
                hour,
                minute
            )

            print("Message scheduled on WhatsApp")

            return True

        except Exception as e:
            print("Error:", e)
            return False