// dashou.c

inherit NPC;

void create()
{
        set_name("����", ({"da shou", "shou" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "���Ǹ��������˺���ר������Ĵ��֡�\n");

        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set("combat_exp", 8000);
//	set("shen", -300);
	set("shen_type", -1);
        set("str", 30);
        set("dex", 20);
        set("con", 15);
        set("int", 15);
        set("attitude","heroism");
        setup();
        set("chat_chance", 5);
        set("chat_msg", ({
"������Ǯׯ�ϰ���˸�����Ҫ��ҪС�Ľ�ѵ��һ�һ�٣�\n",
 "���ְ���˫�ֵ���ָ��������~��~��������\n",
        }) );
        carry_object("/d/city/obj/cloth")->wear();
}

