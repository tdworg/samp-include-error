#include <a_samp>
#include "tdw_error\tdw_error"

main()
{
	new message[TDW_ERR_MESSAGE_SIZE];
	StrError(message, 1);
	printf("Error: %s", message);

	RaiseError(AMX_ERR_MEMACCESS);
}
