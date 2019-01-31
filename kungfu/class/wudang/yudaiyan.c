#include <ansi.h>

inherit NPC;

string ask_me_1();
string ask_me_2();
string ask_wan1();
string ask_dan1();
string ask_dan2();

void create()
{
        set_name("�����", ({ "yu daiyan", "yu" }));
        set("nickname", "�䵱����");
        set("long", 
"������������������ӡ��䵱��������ҡ��򱻼�������������
�°뱲��ֻ���������϶ɹ��ˣ�����һ��ϴ�÷��׵���ɫ������
�κ��㲣���ɫ�Ұף�������������ǻ�����ʲô��\n");
        set("gender", "����");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 5);
        set("max_qi", 900);
        set("max_jing", 900);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 60);
        set("combat_exp", 750000); 
              set("unique", 1);
        set("no_bark",1);

        set_skill("force", 120);
        set_skill("yinyun-ziqi", 120);
        set_skill("dodge", 60);
        set_skill("tiyunzong", 60);
        set_skill("cuff", 90);
        set_skill("taiji-quan", 90);
        set_skill("parry", 60);
        set_skill("sword", 60);
        set_skill("taiji-jian", 60);
        set_skill("literate", 100);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");

        create_family("�䵱��", 2, "����");

        set("inquiry", ([
//              "��ҩ" : (: ask_me_1 :),
                "����" : (: ask_me_2 :),
                "��ת������" : "�Բ�������������û����ҩ��", 
                "���Ľⶾ��" : "�Բ�������������û����ҩ��", 
        ]));

        set("wan_count1", 3);
        set("wan_count2", 3);
        set("letter_count", 1 + random(1));

        setup();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

string ask_me_1()
{
        mapping fam;
        object applicant;
        object ob;
        int exp;

        applicant=this_player();
        if (!(fam = applicant->query("family")) || fam["family_name"] != "�䵱��")
        return RANK_D->query_respect(this_player())+"�뱾��������������̸Ϊ���ɲ�ҩ����";
        exp=(int)applicant->query("combat_exp",1); 
           if(exp>75000)
         return "�㻹�Ƕ���ѧ���գ���ҩ�����ʦ����ȥ���ɡ�\n"; 
        if(exp<10000)
         return "�㻹̫С����ҩ��һ��Σ�գ������ڲ��ʺ�ȥ��\n";

        if((int)applicant->query_skill("medicine", 1) < 20){
         command("shake "+(string)applicant->query("id"));
         return "�㲻ѧ��ݱ�ҩ�������ֱܷ����ҩ��!\n";
         } 
       if(interactive(applicant) && applicant->query_temp("mark/wd_mission"))  
         return "��Ϊʲ�ỹ��ȥ��ҩ��\n";
       if(interactive(applicant) && applicant->query_condition("wd_busy"))  
         return "�����Ѿ����㹻������ȥ��ҩ����\n";
   
        ob = new("/d/wudang/caiyaojob/obj/yaolou");
        ob->move(applicant);
        applicant->set_temp("mark/wd_mission",1);
//        applicant->apply_condition("wd_busy",10);
        return "�䵱������ҩ���Ʊ�������Ҫ����ƣ��ۻƺ��ٻ���ζ��ҩ�Ƴɣ�����\n"+
               "�䵱��ɽ���д˲�ҩ��"+RANK_D->query_respect(applicant)+"����������࣬���Ե��������ҿ���";
}

string ask_me_2()
{
        string *yao_name = ({"����","����","�컨","����","����","ûҩ","����֬","ǧ����","����","Զ־","����","����"});
        mapping fam;
        object applicant;
	 string name;
        name = yao_name[random(sizeof(yao_name))];
        applicant=this_player();
        if (!(fam = applicant->query("family")) || fam["family_name"] != "�䵱��")
        return RANK_D->query_respect(this_player())+"׳ʿ��Ц���ˣ�����������ҵ���֮�£��㻹����ذɣ���";
        if((int)applicant->query("combat_exp", 1) > 2000000){
         command("shake");
         return "���Ѿ������ڽ����ж���һ���ˣ��������»����ñ���ȥ���ɣ�\n";}
        if(applicant->query("job_name") == "�䵱����" || applicant->query_condition("job_busy"))
         return "���ڻ�û�������ʲô�µ��䷽�����ǹ�Щʱ����˵�ɡ�\n";
        if((int)applicant->query("combat_exp", 1) < 500000){
         command("hmm");
         return "�㻹���ڽ����ж�ĥ��ĥ�°ɣ����������Ժ���˵��\n";}
        if((int)applicant->query_skill("medicine", 1) < 80){
         command("shake "+(string)applicant->query("id"));
         return "û�и����ҩ��֪ʶ�����������õĵ�ҩ���㻹���ڱ���ҩ���϶��µ㹦���!\n";}
        if(applicant->query("gender")  =="����"){
         command("sneer");
         return "���������������������������䵱ʦ�ţ���������֮��!\n";}
        if (fam["family_name"] != "�䵱��" || fam["generation"] != 2 )
         return "�����ʦ֮ͽ������ϰϰ����֮������\n";
        if(present("wudang danyao", applicant))
         return "����֮���в�֪�ɷ��޵�֮���������̰������\n";
        if(interactive(applicant) && applicant->query_temp("caiyao_room"))  
         return "�ҵ���Ҫ��ҩ������\n";
        if(interactive(applicant) && applicant->query_temp("caiyao_ok"))  
         return "�ҵ���Ҫ��ҩ������\n";
        if(interactive(applicant) && applicant->query_temp("yao_get"))  
         return "�㻹�ǸϿ�����ҩ��ϸ��˵�ɣ���\n";
        if(interactive(applicant) && applicant->query_temp("yanyao_ok"))  
         return "�㻹�ǸϿ���ҩ�ɣ�����\n";
        if(interactive(applicant) && applicant->query_temp("liandan"))  
         return "������������������ͬ��Ϸ��������\n";
        if(interactive(applicant) && applicant->query_condition("wd_busy"))  
         return "���ڻ�û�������ʲô�µ��䷽�����ǹ�Щʱ����˵�ɡ�\n";

        command("nod");   
        applicant->set_temp("caiyao_room",random(16)+1);
        applicant->set_temp("caiyao_name",name);
        applicant->set("job_name", "�䵱����");
        applicant->apply_condition("job_busy", 9);
//        applicant->apply_condition("wd_busy",10+random(5));
        if(applicant->query("gender")  =="Ů��")
        return "\n���������˼���룬�������һ����Ȼ�������֪�ιʣ�
��Բ������Ѱ[" +name+ "],ʦ���������⣬����ǰȥѰѰ��\n";
        if(applicant->query("gender")  =="����")
        return "\n���������˼���룬�������һ����Ȼ�������֪�ιʣ�
��Բ������Ѱ[" +name+ "],ʦ���������⣬����ǰȥѰѰ��\n";
}

int accept_object(object who, object ob,object me)
{       mapping fam;
        object ob_yaodai;
           int exp,pot;
        object ob_letter;
       
        if (!(fam = this_player()->query("family")) || fam["family_name"] !="�䵱��")
           {
             command("say ���뱾��������������֪Ϊ���ʹ�������? \n");
               return 0;
            }        
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return notify_fail("��û�����������");  
	 
 if(who->query_temp("mark/wd_mission")) {
        if (ob->query("id") != "yao lou" ){
             command("? "+(string)who->query("id"));
             return 0;
             }
       if(!present("ma huang", ob)){
             command("say �����û�вɵ���ư�����");
             return 0;
             }
       if(!present("teng huang", ob)){
             command("say �����û�вɵ��ٻư�����");
             return 0;
             }
       if(!present("xiong huang", ob)){
             command("say �����û�вɵ��ۻư�����");
             return 0;
             }
//   if(!who->query_temp("mark/wd_mission")){
//         command("say �Ҳ�û����ȥ��ҩ������");
//         return 0;
//         }
        command("pat " + who->query("id"));
        command("say ��������ͣ����ձ������ɡ�\n");
        call_out("destroying", 1, ob);        
if( (int)who->query("potential", 1) < (int)who->query("max_pot", 1) ) {
        exp =(3+random(10))*12;
        pot = exp/6 + random(exp/10);
        who->add("combat_exp",exp);
        who->add("potential",pot);
      }
        who->add("wd_job",1);
        who->delete_temp("mark/wd_mission");
        return 1;
} 
if(who->query_temp("caiyao_ok")) {        
         if (ob->query("id") != "yao cai" 
         || strip(ob->query("name")) != who->query_temp("caiyao_name"))
           {
             command("pat "+(string)who->query("id")); 
             command("say ��Щ�������Ƕ���û�ã����Ҿ�������������ɣ�");
             command("hehe "+(string)who->query("id"));
             remove_call_out("destroying");
             call_out("destroying", 1, ob);
             return 1;
             }
        command("congra " + who->query("id"));
        command("say �����ٵô�ҩ�����������������˷�ҩ�������ȥһ�԰ɡ�");
        write("����Ҹ���һ��"WHT"ҩ����\n"NOR);
        remove_call_out("destroying");
        call_out("destroying", 1, ob);
         ob_yaodai=new("/d/wudang/obj/yaodai");
        ob_yaodai->move(who);
        who->add("wd_job",1);
        who->delete_temp("caiyao_name");
        who->delete_temp("caiyao_room");
        who->delete_temp("caiyao_ok");
        who->set_temp("yao_get",1);       
        who->add("potential",90+random(20));
                return 1;
} 

else 
{
         if ((string)ob->query("id") == "changsheng guo")
        {
            if (query("letter_count") > 0) 
              {
                command("ah "+(string)who->query("id"));
                command("say "+"���ĵش��ӣ�ѧ�䶨�д��!��ϧ���Ǹ��зϣ����ܽ����书��\n");
                ob_letter=new("/d/wudang/obj/letters");
                ob_letter->move(who);
                add("letter_count", -1);

                message_vision("$N���һ�����š�\n",this_player());
                command("say �����������ȥ����ʦ��������Ϊʦ�ɣ�Ҳ�������ǽύһ��!\n");
                remove_call_out("destroying");
                call_out("destroying", 1, ob);

               } 
             else
               {
                command("touch "+(string)who->query("id"));
                command("say ���������˸��������ɹ���!\n");
               }
            return 1;
        }
        
	    command("hmm "+ (string)who->query("id"));
        command("say ��Ե�޹����Ҷ�����");
        return 0;     
}
}

void destroying(object obj)
{
     destruct(obj);
     return;
}
