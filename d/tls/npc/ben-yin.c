//cool@SJ,990605
inherit F_MASTER;
inherit NPC;

string ask_kurong();

void create()
{
        set_name("�����ʦ", ({ "benyin dashi","benyin","dashi"}) );
        set("nickname", "����������");
        set("long", "һλ�����ü����ɮ����һϮ��˿ľ�����ġ�
�����׼ұ������У������ʦӦ�ǵ���������
���۵��׼��常��\n");
        set("gender", "����" );
        set("attitude", "friendly");
        set("age", 69);
        set("str", 25);
        set("int", 26);
        set("con", 28);
        set("dex", 26);
        set("unique", 1);
        set("class", "bonze");
        set("shen", 0);
        set("jing", 2000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 100);
        set("qi", 3000);
        set("max_qi", 3000);
        set("neili", 3500);
        set("max_neili", 3500); 
        set("combat_exp", 1350000);
        set_skill("qiantian-yiyang", 165);      
        set_skill("tianlong-xiang", 165);       
        set_skill("yiyang-zhi", 150);
        set_skill("duanjia-jianfa",170);   
        set_skill("buddhism", 165);
        set_skill("literate", 120);
        set_skill("parry", 160);
        set_skill("finger", 165);
        set_skill("sword", 160);
        set_skill("dodge", 165);
        set_skill("kurong-changong", 100);
        set_skill("force", 160);
        set_skill("liumai-shenjian", 120);
        set_skill("medicine", 110);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("sword", "duanjia-jianfa");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");   
        create_family("������", 13, "ɮ��");
	set("inquiry", ([
        "name": "ƶɮ���Ǳ���",
        "����Ժ" : "����Ժ���껨��������������",
	"����" : "���ٴ�ʦ������Ժ����",
	"���ٴ�ʦ" : "���ٴ�ʦ������Ժ����",
	"������" : (: ask_kurong :),
        ]) );
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
              (: perform_action, "finger.sandie" :),
        }));            
        setup();
       
        carry_object("/d/tls/obj/changjian")->wield(); 
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
string ask_kurong()
{
        object me,ob;
		 mapping ob_fam,my_fam;
		ob=this_player();
        me=this_object();
        ob_fam = (mapping)ob->query("family");
        my_fam = (mapping)me->query("family");  
       
      if ((ob_fam && ob_fam["family_name"] != "������")||ob->query("class") != "bonze") 
         return ("�Բ����㲻��ȥ���ſ��ٴ�ʦ��\n");
      if (ob_fam["generation"] == (my_fam["generation"] + 1)){
		  return ("���ֺ��ܣ�������·����һ���֣������Ĳ���������������������һ�������������͵��� \n");
		   } else return ("�㱲�ֲ���������ȥ�ݼ����ٴ�ʦ�� \n");

}
#include "ben.h";
