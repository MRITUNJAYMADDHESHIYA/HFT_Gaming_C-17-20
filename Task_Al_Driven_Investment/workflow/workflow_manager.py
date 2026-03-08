class WorkflowManager:

    def __init__(self, sheet, validator, compliance_ai, scheduler, sender):

        self.sheet         = sheet
        self.validator     = validator
        self.compliance_ai = compliance_ai
        self.scheduler     = scheduler
        self.sender        = sender

    def process(self):

        records = self.sheet.read_pending_rows()
        print("Total pending records: ", len(records))

        for record in records:

            print("--------------------------------")
            print("                                 ")
            print("Processing:", record.name)
            print("Name:", record.name)
            print("Mobile:", record.mobile)
            print("Message:", record.message)

            ####################### Validated ###########
            valid, reason = self.validator.validate(record)

            if not valid:
                print("Invalid record:", record.name, "| Reason:", reason)
                self.sheet.update_status(record.row_id, "Invalid")
                continue
            
            print("validation passed")

            #################### Compilence AI check ##################
            classification = self.compliance_ai.classify(record.message)
            print("ai compliance result: ", classification)

            self.sheet.update_compliance(record.row_id, classification)

            if classification in ["Requires Review", "Rejected"]:
                print("Blocked by compliance:", record.name)
                self.sheet.update_status(record.row_id, "Blocked")
                continue


            ################ Instant sending if empty schedule ##########
            if record.schedule is None or record.schedule == "":
                print("Sending instantly:", record.name)
                self.send_message(record)

            ################ Time schedule ##################
            else:
                print("Scheduling message for:", record.name)

                self.scheduler.schedule_job(record, self.send_message)
                self.sheet.update_status(record.row_id, "Scheduled")


################## Only print the messages, not actually sending them ##############
    def send_message(self, record):

        print(f"sending message to {record.mobile}")
        success = self.sender.send(record)

        if success:
            print("Message sent:", record.name)
            self.sheet.update_status(record.row_id, "Sent")
        else:
            print("Message failed:", record.name)
            self.sheet.update_status(record.row_id, "Failed")

