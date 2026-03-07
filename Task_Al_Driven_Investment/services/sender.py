class MessageSender:

    def send(self, record):

        try:

            print(f"Sending message to {record.mobile}")
            print(record.message)

            # Here integrate SMS/WhatsApp API
            # Twilio or WhatsApp Business API

            return True

        except Exception as e:
            print(e)
            return False