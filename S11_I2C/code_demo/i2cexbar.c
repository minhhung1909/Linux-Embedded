#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

static int i2cexbar_probe_new(struct i2c_client *client){
    pr_info("%s, %d \n", __func__, __LINE__);
    pr_info("I2C device %s probed successfully\n", client->name);
    pr_info("I2C address: 0x%02x\n", client->addr);
    return 0;
}

static int i2cexbar_remove_new(struct i2c_client *client){
    pr_info("%s, %d \n", __func__, __LINE__);
    pr_info("I2C device %s removed successfully\n", client->name);
    return 0;
}

static struct of_device_id i2cexbar_of_id[] = {
    { .compatible = "ssd1306", },
    { /* sentinel */ }
};

static struct i2c_driver i2cexbar = {
    .probe_new = i2cexbar_probe_new,
    .remove = i2cexbar_remove_new,
    .driver = {
        .name = "i2cexbar",
        .of_match_table = i2cexbar_of_id,
    },
};

module_i2c_driver(i2cexbar);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sheldon <hung19092003@gmail.com>");
MODULE_DESCRIPTION("I2C Exbar Driver");
MODULE_VERSION("1.0");