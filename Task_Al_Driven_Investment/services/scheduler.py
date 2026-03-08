import schedule
import time
from datetime import datetime

class Scheduler:

    def __init__(self):
        self.jobs = {}

    def schedule_job(self, record, send_function):
        schedule_time = datetime.strptime(record.schedule, "%Y-%m-%d %H:%M")
        delay = (schedule_time - datetime.now()).total_seconds()
        if delay > 0:
            schedule.every(delay).seconds.do(send_function, record)

    def run(self):
        while True:
            schedule.run_pending()
            time.sleep(1)

            