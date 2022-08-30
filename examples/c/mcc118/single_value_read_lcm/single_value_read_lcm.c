/*****************************************************************************

    MCC 118 Functions Demonstrated:
        mcc118_a_in_read

    Purpose:
        Read a single data value for each channel in a loop.

    Description:
        This example demonstrates acquiring data using a software timed loop
        to read a single value from each selected channel on each iteration
        of the loop.

*****************************************************************************/
#include "../../daqhats_utils.h"

#include <lcm/lcm.h>
#include <stdio.h>


#include <string.h>
#include "exlcm_voltages_t.h"

static int __exlcm_voltages_t_hash_computed;
static uint64_t __exlcm_voltages_t_hash;

uint64_t __exlcm_voltages_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __exlcm_voltages_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = __exlcm_voltages_t_get_hash;
    (void) cp;

    uint64_t hash = (uint64_t)0x0121d000e83f5861LL
         + __int64_t_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __exlcm_voltages_t_get_hash(void)
{
    if (!__exlcm_voltages_t_hash_computed) {
        __exlcm_voltages_t_hash = (int64_t)__exlcm_voltages_t_hash_recursive(NULL);
        __exlcm_voltages_t_hash_computed = 1;
    }

    return __exlcm_voltages_t_hash;
}

int __exlcm_voltages_t_encode_array(void *buf, int offset, int maxlen, const exlcm_voltages_t *p, int elements)
{
    int pos = 0, element;
    int thislen;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].timestamp), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].voltages, 5);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int exlcm_voltages_t_encode(void *buf, int offset, int maxlen, const exlcm_voltages_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __exlcm_voltages_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __exlcm_voltages_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __exlcm_voltages_t_encoded_array_size(const exlcm_voltages_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int64_t_encoded_array_size(&(p[element].timestamp), 1);

        size += __double_encoded_array_size(p[element].voltages, 5);

    }
    return size;
}

int exlcm_voltages_t_encoded_size(const exlcm_voltages_t *p)
{
    return 8 + __exlcm_voltages_t_encoded_array_size(p, 1);
}

int __exlcm_voltages_t_decode_array(const void *buf, int offset, int maxlen, exlcm_voltages_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].timestamp), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].voltages, 5);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __exlcm_voltages_t_decode_array_cleanup(exlcm_voltages_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_decode_array_cleanup(&(p[element].timestamp), 1);

        __double_decode_array_cleanup(p[element].voltages, 5);

    }
    return 0;
}

int exlcm_voltages_t_decode(const void *buf, int offset, int maxlen, exlcm_voltages_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __exlcm_voltages_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __exlcm_voltages_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int exlcm_voltages_t_decode_cleanup(exlcm_voltages_t *p)
{
    return __exlcm_voltages_t_decode_array_cleanup(p, 1);
}

int __exlcm_voltages_t_clone_array(const exlcm_voltages_t *p, exlcm_voltages_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_clone_array(&(p[element].timestamp), &(q[element].timestamp), 1);

        __double_clone_array(p[element].voltages, q[element].voltages, 5);

    }
    return 0;
}

exlcm_voltages_t *exlcm_voltages_t_copy(const exlcm_voltages_t *p)
{
    exlcm_voltages_t *q = (exlcm_voltages_t*) malloc(sizeof(exlcm_voltages_t));
    __exlcm_voltages_t_clone_array(p, q, 1);
    return q;
}

void exlcm_voltages_t_destroy(exlcm_voltages_t *p)
{
    __exlcm_voltages_t_decode_array_cleanup(p, 1);
    free(p);
}

int exlcm_voltages_t_publish(lcm_t *lc, const char *channel, const exlcm_voltages_t *p)
{
      int max_data_size = exlcm_voltages_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = exlcm_voltages_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _exlcm_voltages_t_subscription_t {
    exlcm_voltages_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void exlcm_voltages_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    exlcm_voltages_t p;
    memset(&p, 0, sizeof(exlcm_voltages_t));
    status = exlcm_voltages_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding exlcm_voltages_t!!!\n", status);
        return;
    }

    exlcm_voltages_t_subscription_t *h = (exlcm_voltages_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    exlcm_voltages_t_decode_cleanup (&p);
}

exlcm_voltages_t_subscription_t* exlcm_voltages_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    exlcm_voltages_t_handler_t f, void *userdata)
{
    exlcm_voltages_t_subscription_t *n = (exlcm_voltages_t_subscription_t*)
                       malloc(sizeof(exlcm_voltages_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 exlcm_voltages_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg exlcm_voltages_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int exlcm_voltages_t_subscription_set_queue_capacity (exlcm_voltages_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int exlcm_voltages_t_unsubscribe(lcm_t *lcm, exlcm_voltages_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe exlcm_voltages_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

int main()
{
    // mcc118_a_in_read() variables
    uint8_t address;
    uint8_t channel = 0;
    uint32_t options = OPTS_DEFAULT;
    double value;
    double voltages[5];

    uint8_t low_chan = 0;
    uint8_t high_chan = 4;

    char display_string[256] = "";
    char c;

    int result = RESULT_SUCCESS;
    int samples_per_channel = 0;
    int sample_interval = 500;  // ms
    int mcc118_num_channels = mcc118_info()->NUM_AI_CHANNELS;

    // Ensure low_chan and high_chan are valid
    if ((low_chan >= mcc118_num_channels) || 
        (high_chan >= mcc118_num_channels))
    {
        fprintf(stderr, "Error: Invalid channel - must be 0 - %d.\n",
            mcc118_num_channels - 1);
        return -1;
    }
    if (low_chan > high_chan)
    {
        fprintf(stderr, "Error: Invalid channels - "
            "high_chan must be greater than or equal to low_chan\n");
        return -1;
    }

    // Determine the address of the device to be used
    if (select_hat_device(HAT_ID_MCC_118, &address) != 0)
    {
        return -1;
    }

    // Open a connection to each device
    result = mcc118_open(address);
    printf("\nResult\n");
    printf("%d\n", result);

    STOP_ON_ERROR(result);

    printf("\nMCC 118 single data value read example\n");
    printf("    Function demonstrated: mcc118_a_in_read\n");
    printf("    Channels: %d - %d\n", low_chan, high_chan);
    convert_options_to_string(options, display_string);
    printf("    Options: %s\n", display_string);

    printf("\nPress 'Enter' to continue\n");

    scanf("%c", &c);

    printf("Acquiring data ... Press 'Enter' to abort\n\n");

    // Display the header row for the data table
    printf("  Samples/Channel");
    for (channel = low_chan; channel <= high_chan; channel++)
    {
        printf("     Channel %d", channel);
    }
    printf("\n");

    lcm_t *lcm = lcm_create(NULL);
    if (!lcm)
        return 1;

    while (!enter_press())
    {
        // Display the updated samples per channel
        printf("\r%17d", ++samples_per_channel);
        // Read a single value from each selected channel
        for (channel = low_chan; channel <= high_chan; channel++)
        {
            result = mcc118_a_in_read(address, channel, options, &value);
            STOP_ON_ERROR(result);
            voltages[channel] = value;
            printf("%12.5f V", value);
        };

        exlcm_voltages_t my_data = {
            .timestamp = 0, .voltages[0] = voltages[0], .voltages[1] = voltages[1], .voltages[2] = voltages[2], .voltages[3] = voltages[3], .voltages[4] = voltages[4],
        };

        exlcm_voltages_t_publish(lcm, "VOLTAGES", &my_data);

        fflush(stdout);
        usleep(sample_interval * 1000);
    }

    lcm_destroy(lcm);

stop:
    result = mcc118_close(address);
    print_error(result);

    return 0;
}
