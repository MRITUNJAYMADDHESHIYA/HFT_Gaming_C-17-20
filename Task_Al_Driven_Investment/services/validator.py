import re
from datetime import datetime


class Validator:

    allowed_categories = [
        "Performance Update",
        "Research Insight",
        "Product Communication",
        "Marketing"
    ]

    def validate(self, record):

        ################ Mobile number format ################
        mobile = str(record.mobile).strip()

        if not re.match(r"^[6-9]\d{9}$", mobile):
            return False, "Invalid Mobile"

        ################ Non-empty message ################
        if not record.message or not record.message.strip():
            return False, "Empty Message"

        ################ Schedule validation ################
        if record.schedule and str(record.schedule).strip():

            try:
                schedule_time = datetime.strptime(record.schedule, "%Y-%m-%d %H:%M")
            except:
                return False, "Invalid datetime format (YYYY-MM-DD HH:MM)"

            ################ Schedule should not be in past ################
            if schedule_time < datetime.now():
                return False, "Schedule in past"

        ################ Category validation ################
        if record.category not in self.allowed_categories:
            return False, "Invalid category"

        return True, "Valid"