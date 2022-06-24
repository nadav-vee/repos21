# Protocol Constants

CMD_FIELD_LENGTH = 16	# Exact length of cmd field (in bytes)
LENGTH_FIELD_LENGTH = 4   # Exact length of length field (in bytes)
MAX_DATA_LENGTH = 10**LENGTH_FIELD_LENGTH-1  # Max size of data field according to protocol
MSG_HEADER_LENGTH = CMD_FIELD_LENGTH + 1 + LENGTH_FIELD_LENGTH + 1  # Exact size of header (CMD+LENGTH fields)
MAX_MSG_LENGTH = MSG_HEADER_LENGTH + MAX_DATA_LENGTH  # Max size of total message
DELIMITER = "|"  # Delimiter character in protocol
DATA_DELIMITER = "#"  # Delimiter in the data part of the message

# Protocol Messages 
# In this dictionary we will have all the client and server command names

PROTOCOL_CLIENT = {
"login_msg" : "LOGIN",
"logout_msg" : "LOGOUT",
"get_score" : "MY_SCORE",
"get_score_table" : "HIGHSCORE",
"get_question" : "GET_QUESTION",
"send_answer" : "SEND_ANSWER",
"get_logged_users" : "LOGGED"
} # .. Add more commands if needed


PROTOCOL_SERVER = {
"login_ok_msg" : "LOGIN_OK",
"login_failed_msg" : "ERROR",
"action_successful" : "SUCCESS",
"action_failed" : "ERROR",
} # ..  Add more commands if needed


# Other constants

ERROR_RETURN = None  # What is returned in case of an error


def build_message(cmd, data):
	"""
	Gets command name (str) and data field (str) and creates a valid protocol message
	Returns: str, or None if error occured
	"""
	# Implement code ...

    #return full_msg
	if(cmd == None or data == None):
		return None
	return "{:<16}".format(cmd) + "|{:0>4}".format(len(data))+ "|{}".format(data)



def parse_message(data):
	"""
	Parses protocol message and returns command name and data field
	Returns: cmd (str), data (str). If some error occured, returns None, None
	"""
	# Implement code ...

    # The function should return 2 values
    #return cmd, msg
	if(data.count("|") == 2):
		if(data[17:21].isdigit()):
			tmplen = data.rfind("|")
			if(int(data[17:21]) == len(data) - 22):
				lpromsg = data.split("|")
				return lpromsg[0].strip(), lpromsg[2]
	return None, None

	
def split_data(msg, expected_fields):
	"""
	Helper method. gets a string and number of expected fields in it. Splits the string 
	using protocol's data field delimiter (|#) and validates that there are correct number of fields.
	Returns: list of fields if all ok. If some error occured, returns None
	"""

	if(msg.count("#") != expected_fields-1):
		return ERROR_RETURN
	else:
		return msg.split("#", expected_fields-1)



def join_data(msg_fields):
	"""
	Helper method. Gets a list, joins all of it's fields to one string divided by the data delimiter. 
	Returns: string that looks like cell1#cell2#cell3
	"""
	# Implement code ...
	return "#".join(msg_fields)
