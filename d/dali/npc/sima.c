// NPC sima.c
inherit NPC;
//inherit F_MASTER;

#include <ansi.h>
string huanggong();

void create()
{
        set_name("����", ({ "fan ye", "fan"}));
        set("title", "�����˾��");
        set("gender", "����");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "�����е���ģ����Ž��йٷ���Ŀ����棬����
�����������ı�ԣ��Ӵ���Ϊ�ٶ��깦ѫ�պա�\n");
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 2500);
        set("max_neili", 2500);        
        set("eff_jingli",1000);
        set("jiali",50);
        set("combat_exp", 700000);
        set("shen_type", 1);
        set("attitude", "peaceful");
//      create_family("����", 3 , "����");
         
        set_skill("force",120);
        set_skill("sword",135);
        set_skill("strike",130);
        set_skill("qingyan-zhang",130);
        set_skill("dodge",100);
        set_skill("tianlong-xiang",100);
        set_skill("parry",120);
        set_skill("qiantian-yiyang",120);
        set_skill("duanjia-jianfa",135);
        map_skill("parry", "duanjia-jianfa");
        map_skill("dodge", "tianlong-xiang");
        map_skill("strike","qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("sword", "duanjia-jianfa");
        prepare_skill("strike","qingyan-zhang");

        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);        
        
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object(__DIR__"obj/zipao")->wear();
}
