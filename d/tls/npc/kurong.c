//update by cool 98.2.18

inherit F_MASTER;
inherit NPC;

int ask_xingyue(object who);
string ask_liumai1();
string ask_liumai2();
int ask_dudan(object who);   

void create()
{
     object ob;
        set_name("���ٳ���", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "�����³���");
         set("long", 
" ���ٳ�����������֮������ߵ�һ����ɫ����
Ƥ���⻬������Ӥ�����ұߵ�һ��ȴ��ݹǣ�����
һ�Ž��Ƶ���Ƥ֮��ȫ�޼��⣬��ͷͻ�˳�������
Ȼ���ǰ�����ù�ͷ�������������б�����ߣ���
������ο�������ʮ�꣬��������ɮ�ڣ�˭Ҳû��
��������Ŀ��\n");
        set("gender", "����" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("cor", 27);
        set("cps", 32);
        set("int", 25);
        set("per",23);
        set("max_jing",5000);
        set("eff_jingli",3500);
        set("max_qi",7000);
        set("jiali",100);
        set("neili",15000);
        set("max_neili",15000); 
        set("rank_info/respect", "��ɮ");
        create_family("������", 12, "ɮ��");
        set("combat_exp", 2850000);
        set("score", 0);
        set("chat_chance_combat", 60);
        set("chat_msg_combat",({ 
                (: exert_function, "ku" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 300);
        set_skill("dodge", 300);
        set_skill("medicine", 180);
        set_skill("force", 200);
        set_skill("finger", 300);
        set_skill("whip", 300);
        set_skill("liumai-jianzhen",200);
        set_skill("cihang-bian", 300);
        set_skill("duanjia-jianfa", 300);
        set_skill("sword", 300);
        set_skill("strike", 300);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("qiantian-yiyang", 220);
        set_skill("liumai-shenjian", 40);
        set_skill("kurong-changong", 220);
        set_skill("qingyan-zhang", 280);
        set_skill("yiyang-zhi", 300);
        set_skill("tianlong-xiang", 300);
        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 
        set_temp("apply/armor", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);
        set("inquiry", ([
        "name": "ƶɮ���ǿ���",
     "����" : (: ask_xingyue :),
         "����" : (: ask_dudan :),
        "���ƶ�" : (: ask_liumai2 :),
        "����" : (: ask_liumai1 :),
        ]) );

        set("env/һ��ָ", 3);
        setup();
        
        if (clonep(this_object()))  {
        if (ob = carry_object("/clone/weapon/xingyue")) ob->wield(); }
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "kurong.h"

