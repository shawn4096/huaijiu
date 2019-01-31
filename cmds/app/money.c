// full.c for apprentice
// written by snowman@SJ 29/10/1999

inherit F_CLEAN_UP;
 
int main(object me,string arg)
{
        string kind;
        int amount;
        object n_money;

        if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
          return notify_fail("[topless]: wave <∂‡…Ÿ«Æ> <«Æ±“÷÷¿‡>\n");

        n_money = present(kind + "_money", me);
        if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
                return notify_fail("ƒ„Õ⁄¡À∞ÎÃÏ»¥ ≤√¥“≤√ª”–Õ⁄≥ˆ¿¥°£\n");
        if( amount < 1 )
                return notify_fail("ƒ„Õ⁄¡À∞ÎÃÏ»¥ ≤√¥“≤√ª”–Õ⁄≥ˆ¿¥°£\n");

        if( !n_money ) {
                n_money = new("/clone/money/" + kind);
                n_money->move(me);
                n_money->set_amount(amount);
        } else
                n_money->add_amount(amount);

	message_vision( sprintf("$Nƒ√≥ˆ“ª’≈VISAø®£¨¥”ATM÷–»°≥ˆ¡À%s%s%s°£\n",
                        chinese_number(amount),
                        n_money->query("base_unit"),
                        n_money->query("name")),me);
        log_file("static/HOWG",sprintf("%s(%s) ¥”ATM÷–»°≥ˆ¡À%s%s%s° on %s\n",me->name(1), geteuid(me),chinese_number(amount), n_money->query("base_unit"),n_money->query("name"), ctime(time()) ) );
        return 1;
}

int help(object me)
{
        write(@HELP
÷∏¡Ó∏Ò Ω: money <∂‡…Ÿ«Æ> <«Æ±“÷÷¿‡>
 
 »°«Æ°£

HELP );
        return 1;
}
