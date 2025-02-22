// NPC: /d/huashan/npc/teller.c
// Date: Look 99/03/25

inherit NPC;

void tell_fortune();

int do_forge();

void create()
{
    set_name("李铁嘴", ({ "li tiezui", "li" }) );
	set("gender", "男性" );
	set("age", 48);
	set("long", 
"李铁嘴是个买卜算卦的江湖术士，兼代客写书信、调幅。\n");
       set("str", 25);
       set("dex", 20);
	set("con", 17);
       set("int", 15);
	set("shen_type", -1);

       set_skill("unarmed", 20);
	set_skill("dodge", 20);
       set_temp("apply/attack", 25);
       set_temp("apply/defense", 25);
       set("combat_exp", 3000);

	set("attitude", "peaceful");
       set("inquiry", ([
       	"算命" : "李铁嘴说道：我今天没心情，不算，不算。\n",
		"写信" : "李铁嘴说道：代客写信，每页五十文。\n",
		"写调幅" : "李铁嘴说道：可以用各家字迹写调幅，每幅五两白银。\n",
//		"伪造" : (: do_forge :),
	        ]) );
	setup();
	carry_object(ARMOR_D("armor/cloth"))->wear();

	add_money("silver", 5);
}

int do_forge()
{
	say("李铁嘴两只眼睛四下扫了扫，「嘿嘿嘿」的干笑了几声...\n");
	write(
"李铁嘴轻声跟你说道：不是我吹牛，保证蓦的跟原来字体一模一样，每封信\n"
"	            五十两白银，不二价。\n");
	this_player()->set_temp("marks/李", 1);
	return 1;
}

int accept_object(object who, object ob)
{
	object letter;

	if ((string)ob->query("name")=="信纸") {
	        if( who->query_temp("marks/李") ) {
			who->set_temp("marks/李3", 1);
			write(
"李铁嘴对你说道：造封信容易，先拿五十两银子来。\n");
			who->set_temp("marks/李", 0);
			call_out("destroy", 1, ob);
			return 1;
		} else if( who->query_temp("marks/李2") ) {
                        write(
"李铁嘴皮笑肉不笑的对你说道：伪造这封信可是关系重大啊，得多收五十两。\n");
                        who->set_temp("marks/李4", 1);
			who->set_temp("marks/李2", 0);
			call_out("destroy", 1, ob);
                        return 1;
                }
//              say("李铁嘴说：这是写好了的信，给我干什么?\n");
                return 0;
	}
       
	if( ob->value() >= 5000 ) {
		 if( who->query_temp("marks/李4") ) {
			write(
"李铁嘴对你说道：这封信是造好了，但" + RANK_D->query_respect(who) + 
"要是出了事，千万别把我说出来呀。\n");
			say("李铁嘴给了" + who->query("name") + "一封手信。\n");
			who->set_temp("marks/李4", 0);
			letter = new(__DIR__"obj/letter");
			letter->move(who);
			return 1;
		}
		if( who->query_temp("marks/李3") ) {
			write(
"李铁嘴皮笑肉不笑的对你说道：伪造这封信可是关系重大啊，得多收五十两。\n");
			who->set_temp("marks/李4", 1);
			who->set_temp("marks/李3", 0);
			return 1;
		} 
		if( who->query_temp("marks/李") ) {
			write(
"李铁嘴对你说道：你想伪造什么啊? 总得拿个样子来吧。\n");
		who->set_temp("marks/李2", 1);
		who->set_temp("marks/李", 0);
		return 1;
		}
                say(
"李铁嘴一面急忙把钱收起来，一面笑嘻嘻说道：" + RANK_D->query_respect(who) +
"，这怎么敢当。\n");
		return 1;
	}
        if( ob->value() >= 500 ) {
		say(
"李铁嘴笑嘻嘻说道：调幅写好了，请您收起来吧，多谢关照。\n");
		return 1;
	}
	if( ob->value() >= 50 ) {
		say(
"李铁嘴笑嘻嘻说道：信写完了，您收好了，多谢关照。\n");
		return 1;
	}
	return 0;
}

void destroy (object ob)
{
        destruct(ob);
}
