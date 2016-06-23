#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "simple_argp 0.1";
const char *argp_program_bug_address =
           "<some_email_address@you_care_about.com>";

static char doc[] =
"short program to show the use of argp\nThis program does little";

static char args_doc[] = "ARG1 ARG2";

/* initialise an argp_option struct with the options we except */
static struct argp_option options[] =
{
  {"verbose", 'v', 0,      0, "Produce verbose output" },
  {"output",  'o', "FILE", 0, "Output to FILE" },
  { 0 }
};

/* Used by `main' to communicate with `parse_opt'. */
struct arguments
{
  char *args[2];                /* ARG1 & ARG2 */
  int silent, verbose;
  char *output_file;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the INPUT argument from `argp_parse', which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = /*static_cast<arguments *>*/(state->input);

  switch (key)
    {
    case 'q': case 's':
      arguments->silent = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 2)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main (int argc, char **argv)
{
  struct arguments arguments;

  /* Default values. */
  arguments.silent = 0;
  arguments.verbose = 0;
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by `parse_opt' will
     be reflected in `arguments'. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  printf ("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\n"
          "VERBOSE = %s\nSILENT = %s\n",
          arguments.args[0], arguments.args[1],
          arguments.output_file,
          arguments.verbose ? "yes" : "no",
          arguments.silent ? "yes" : "no");

  exit (0);
}
