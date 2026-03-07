class WorkflowManager:

    def __init__(self, sheet, validator, compliance_ai, scheduler, sender):

        self.sheet = sheet
        self.validator = validator
        self.compliance_ai = compliance_ai
        self.scheduler = scheduler
        self.sender = sender

    def process(self):

        records = self.sheet.read_pending_rows()

        for record in records:

            # Step 1: Validate data
            valid, reason = self.validator.validate(record)

            if not valid:
                print("Invalid record:", record.name)
                self.sheet.update_status(record.row_id, "Invalid")
                continue


            # Step 2: Compliance AI check
            classification = self.compliance_ai.classify(record.message)
            self.sheet.update_compliance(record.row_id, classification)

            if classification != "Approved":
                print("Blocked by compliance:", record.name)
                self.sheet.update_status(record.row_id, "Blocked")
                continue


            # Step 3: Instant send OR Schedule
            if record.schedule is None or record.schedule == "":

                print("Sending instantly:", record.name)

                self.send_message(record)

            else:

                print("Scheduling message for:", record.name)

                self.scheduler.schedule_job(record, self.send_message)
                self.sheet.update_status(record.row_id, "Scheduled")


    def send_message(self, record):

        success = self.sender.send(record)

        if success:
            print("Message sent:", record.name)
            self.sheet.update_status(record.row_id, "Sent")
        else:
            print("Message failed:", record.name)
            self.sheet.update_status(record.row_id, "Failed")