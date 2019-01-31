// ping.c 平一指

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("张老板", ({ "zhang laoban", "zhang", "laoban" }));
	set("title", "药铺老板");
	set("gender", "男性");
	set("long", "他是大理城里唯一的医师。\n");
	set("age", 65);
        set("unique", 1);
	set("int", 30);
        set("no_get","张老板对你来说太重了。\n");
	
	set("qi", 90000);
	set("max_qi", 90000);
	set("jing", 8000);
	set("max_jing", 8000);
	set("jingli", 6000);
	set("neili", 80000);
	set("max_neili", 800);
	set("jiali", 5);
	set("shen_type", 1);

	set("combat_exp", 5000000);
	set("attitude", "peaceful");

	set_skill("unarmed", 60);
	set_skill("force", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
        set_skill("liandan-shu", 300);
	set_temp("apply/attack", 700);
	set_temp("apply/defense", 700);
	set_temp("apply/damage", 500);

	setup();
	add_money("silver", 5);
	carry_object("/clone/armor/cloth")->wear();
}

int recognize_apprentice(object ob)
{
	int money = 50, level = ob->query_skill("liandan-shu", 1);

	if (level >= 300){
		message_vision(CYN"\n$N对着$n端详了一番道：“你的炼丹术已经登峰造极，我没什么可以教你的了。”\n"NOR, this_object(), ob);
		return 0;
	}
	
	if (level > 29) money = 100;
	if (level > 59) money = 200;
	if (level > 89) money = 1000;
	if (level > 119) money = 2000;

	ob->delete_temp("mark/liandan");
	switch (MONEY_D->player_pay(ob, money)) {
		case 0:
		case 2:
		return notify_fail("你现在学习一次所需要的费用是"+MONEY_D->money_str(money)+"，你身上带的零钱不够了。\n");
	}
        ob->set_temp("mark/liandan", 1);
        return 1;
}
