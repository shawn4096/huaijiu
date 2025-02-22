//  monk.c

inherit NPC;

void create()
{
	set_name("小和尚", ({ "young monk","monk" }) );
	set("class", "bonze");
	set("gender", "男性");
	set("age", 15);
	set("long",
		"他是扬洲城隍庙新收的小徒弟。正在认真的打扫厅院。\n");
	set("title", "城隍庙小和尚");
	set("combat_exp", 9000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("inquiry", ([
	"mud" :"这儿是刚刚经过了狂风暴雨般的疯狂建设后完成的全新ＭＵＤ！",
	]) );
	setup();

	set("apply/attack", 60);
	set("apply/defense", 60);

	set_skill("unarmed", 30);
	set_skill("sword", 40);
	set_skill("parry", 30);
	set_skill("dodge", 36);
	setup();

	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 1);
}       
