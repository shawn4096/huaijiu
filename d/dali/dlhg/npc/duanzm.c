// king.c ������
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string enter();
string qinwang(object ob);
void create()
{
        set_name("������", ({ "duan zhengming", "duan", "master" }) );
        set("nickname", HIW"������"NOR);
        set("title","����ʵ�");
        set("gender", "����" );
        set("age", 48);
        set("str", 28);
        set("con", 28);
        set("dex", 28);
        set("int", 28);
        set("per", 26);
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("neili", 4000);
        set("qi", 4000);
        set("jingli", 3000);
        set("max_neili", 4000);
        set("jiali", 80);

        set("rank_info/respect", "����");
        create_family("������", 13, "�׼ҵ���");
        set("long", 
        "������ȥƽ�׽��������з�ȣ�����������üĿ֮��͸��һ�ɱ��˵�Ӣ����\n");
        set("combat_exp", 1600000);
        set("score", 200000);              

        set_skill("parry", 200);
        set_skill("dodge", 180);
        set_skill("buddhism",180);
        set_skill("force", 200);
        set_skill("literate", 150);
        set_skill("sword", 180);
        set_skill("duanjia-jianfa", 180);
        set_skill("cuff", 200);
        set_skill("duanjia-quan", 200);
        set_skill("yiyang-zhi", 200);
        set_skill("finger", 200);
        set_skill("qiantian-yiyang", 200);
        set_skill("tianlong-xiang", 200);
		

        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "duanjia-jianfa");
        map_skill("sword", "duanjia-jianfa");
        map_skill("force", "qiantian-yiyang");
        map_skill("cuff", "duanjia-quan");
	map_skill("finger","yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");
        set("inquiry", ([
        "���" : (: enter :), 
        "����" : (: qinwang :),
        "name": "�޾��Ǳ����۶�������",
        "here": "������Ǵ���ʹ���",        
        ]) );

        setup();
        carry_object("/d/dali/npc/obj/huangpao")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
        object ob,me;
   //     mapping my_fam;
  //      int i;
        me=this_object();
        ob = this_player();
 //       i = ob->query_skill("liumai-shenjian",1);
 //       if (ob->query("family"))
 //       my_fam=ob->query("family"); 
        ::init();
        if (interactive(ob = this_player()) && living(this_object()) &&
                (int)ob->query_temp("killqueen")) {
                command ("say �㾹��ɱ�ҵĻʺ���������\n");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, ob);
        }
/*                     
       if ((my_fam["family_name"] == "����")){
          ob->set("family/family_name","������");
          if (my_fam["generation"]<4) 
          {
          ob->set("family/generation", 14);
          ob->set_skill("buddhism",140);
        } else ob->set("family/generation", 15);
         if (ob->query_skill("liumai-shenjian",1)) {
	  ob->set_skill("yiyang-zhi",i);
	  ob->delete_skill("liumai-shenjian");
	  ob->set_skill("kurong-changong",100);
	  command ("say ������ܽӿ���ʮ��,������ѧϰ���� \n");
	        }
	      	
		command ("say ����,�����������ϲ�,������������׼ҵ�����! \n");
          }
 */         
}

string enter()
{
        object ob;
        string target;
        ob = this_player();
        if ( ob->query("combat_exp") < 100000)
           return "������󹬸���";
        if ( ob->query_temp("fan")){
           string book;
           book=ob->query_temp("book_target");
           return("����ȥ��"+book+CYN"��������ȥ��"NOR);
           }
        switch  (random(7)){
        case 0: target = HIW"����ƪ"NOR; break;
        case 1: target = HIW"����ƪ"NOR; break;
        case 2: target = HIW"ҹ��ƪ"NOR; break;
        case 3: target = HIW"Ǭ����ƪ"NOR; break;
        case 4: target = HIW"������ƪ"NOR; break;
        case 5: target = HIW"��¥��ƪ"NOR; break;
        case 6: target = HIW"������ƪ"NOR; break;
        case 7: target = HIW"Ħ������ƪ"NOR; break;
        }
        ob->set_temp("fan",1);
        ob->set_temp("book_target",target);
        return("����󹬣��Ȱ��Ұ������˲���"+target+CYN"������"NOR);   
}

string qinwang(object ob)
{       
       string new_title,title,*title1,*title2;
       mapping fam;
       ob=this_player();
       fam = ob->query("family");       
       title1 =({ "��","ƽ","��","Ǭ","��" });
       title2 =({ "��","��","��","��" });
       if ((!fam)||(fam["family_name"] != "������"))
          return RANK_D->query_respect(ob)+"�뱾��������������֪�˻��Ӻ�̸��";  
        if (ob->query("tls")&&ob->query("class")=="bonze")
                return RANK_D->query_respect(ob) + "�Ѿ���Ϊ�����¸�ɮ�����������Ȼ�ǲ��ʺ����.";
       if (ob->query("dali_job") < 3000 && ob->query_skill("qiantian-yiyang",1) < 160)
          return RANK_D->query_respect(ob) + "Ϊ�������Ļ������������Ϊ��ү�ˣ�";
       if (stringp(ob->query("qinwang")))
          return RANK_D->query_respect(ob) + "�Ѿ����ҳ������ˣ���ô����������";
       title= title1[random(sizeof(title1))]+title2[random(sizeof(title2))]+"��";
       new_title= "�����"+title;
       ob->set("title",HIW + new_title + NOR);
       ob->set("qinwang", title);
       command("chat ���������������޷�" + ob->query("name")+"Ϊ��"+new_title+"��");
       return "�ðɣ������Ϳ๦�ߣ��޾ͷ���Ϊ"+ new_title +"��";       
       
}

void attempt_apprentice(object ob)
{     
        string name, new_name, *prename;
        prename = ({ "��", "��" });
        if (ob->query("tls")&&ob->query("class")=="bone") {
             command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
             return;
             } 
        if( (int)ob->query_skill("qiantian-yiyang",1) < 140 ){      
             command ("hmm");
             command ("say ��Ǭ��һ�������֮��ҿɲ����㣡");
             return;
             }
        if(ob->query_int() < 33){
             command("say ��ѧ֮���������Ըߣ����ҿ�" + RANK_D->query_respect(ob) + "�������ƺ�������");
             return;
             }
        if(ob->query("shen") < 0){
             command("say ���������û��ң�����λ" + RANK_D->query_respect(ob) + "��¶�׹⣬�ҿ����ʺ����Ҵ������ȥ�ˡ�");
             return;
             }
        command("smile");
        command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
        name = ob->query("name");
        new_name = prename[random(sizeof(prename))] + name[<4..<1];
        command("say ���Ҷμң��ӽ��Ժ�������־ͽ���" + new_name + "��");  
        ob->set("name", new_name);     
        command("recruit " + ob->query("id") );
        if (!ob->query("qinwang")) ob->set("title","�������ǰ����");
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        ob->set("class", "officer");
}

int accept_object(object who, object ob)
{
        string bookname;
        bookname=ob->query("name");
        if ((bookname!=HIW"����ƪ"NOR)
          &&(bookname!=HIW"����ƪ"NOR)
          &&(bookname!=HIW"ҹ��ƪ"NOR)
          &&(bookname!=HIW"Ǭ����ƪ"NOR)
          &&(bookname!=HIW"������ƪ"NOR)
          &&(bookname!=HIW"��¥��ƪ"NOR)
          &&(bookname!=HIW"������ƪ"NOR)
          &&(bookname!=HIW"Ħ������ƪ"NOR))
            return notify_fail("����������ҡͷ������Ҫ�ⶫ��û�ð���\n");
       if ( bookname==this_player()->query_temp("book_target")){
          if ( ob->query_temp("find") == who->query("id")){ 
              command("smile");
              command("say �ܺã�����Խ����ˡ�");
              who->set_temp("enter",1);
              who->delete_temp("book");
              call_out("destroying", 1, ob);
              return 1;
              }
              command("hmm");
              command("say ����������ҵ��İɡ�");
              call_out("destroying", 1, ob);
              return 1;
              }
       else{
              command("hmm");
              command("say �ⲻ����Ҫ���飬����ȥ�ҡ�");    
              call_out("destroying", 1, ob);
              return 1;
              }        
}

void destroying(object ob)
{
        destruct(ob);
        return;
}
