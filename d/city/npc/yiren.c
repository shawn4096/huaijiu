// liumangtou.c ��åͷ

inherit NPC;

void create()
{
        set_name("����", ({ "yiren", "man" }));
	set("gender", "����");
        set("age", 43);
        set("long", "����һ�����ϴ����Ľ������ˡ�\n");
	
	set("combat_exp", 7000);
        set("shen_type", 0);
	set("attitude", "peaceful");
	
          set_skill("unarmed", 25);
          set_skill("dodge", 25);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);

	setup();
	carry_object("/clone/misc/cloth")->wear();
          add_money("silver", 10);
}
