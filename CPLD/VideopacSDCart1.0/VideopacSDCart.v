`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:30:17 05/23/2020 
// Design Name: 
// Module Name:    VideopacSDCart 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module VideopacSDCart(
    output reg [14:0] RAMA,
    output reg RAMOE,
    output reg RAMCS,
    inout [0:7] RAMD,
    output reg RAMWE,	 
    input [14:0] ARDA,
    inout [7:0] ARDD,
    input ARDOE,
    input ARDWE,
    input [2:0] PAGEMODE,
    input [11:0] BUSA,
    inout [7:0] BUSD,
    input P10,
    input P11,
    input P14,
    input T0,
    input PSEN,
    input EXTRAM,
    input BUSWR
    );
	 
	reg [7:0] bankvp = 8'd255;
//	reg [7:0] banksel = 8'b11111111;
	reg [7:0] RAMD_out = 8'b00000000;
	reg [7:0] BUSD_out = 8'b00000000;
	reg [7:0] ARDD_out = 8'b00000000;
//	reg fase = 1'b0;
	
//	reg result_ready = 1'b0;

//	wire romstart;
	
	wire BUSD_en;
	wire chgbankvp_clk;
	
	wire xromPSEN;
	
	assign xromPSEN = (~(P11 & EXTRAM) & PSEN);
	
	assign chgbankvp_clk = ~BUSA[7] | P14 | BUSWR;
	
//	assign romstart = /*(PSEN==0) && */((BUSA[11]==1) || (BUSA[10]==1)) &&(BUSA[0]==0);
	
//	assign T0 = 1'bz;
	
	always @(posedge chgbankvp_clk) begin
//		bankvp[2:0] <= BUSD[2:0];
		bankvp <= BUSD;
	end
	
//	always @(posedge romstart) begin
//		if (PAGEMODE[2]==1)
//			fase = 1'b0;
//		else 
//			fase=1'b1;
//	end
	
	always @(*)
	begin
		case (PAGEMODE)
							// P10-P11
			3'b000: begin
				RAMA = {1'b0,1'b0,P11,P10,BUSA[11],BUSA[9:0]};
				RAMD_out = BUSD;
				BUSD_out = RAMD;
				RAMWE = 1'b1;
				RAMCS = 1'b0;
				RAMOE = PSEN;
				ARDD_out = RAMD;
			end
							// vp+
			3'b001: begin
				if (P10==1'b0) begin
					RAMA = {1'b0,bankvp[2:0],BUSA[11],BUSA[9:0]};
				end else begin
					RAMA = {1'b0,3'b111,BUSA[11],BUSA[9:0]};
				end
				RAMD_out = BUSD;
				BUSD_out = RAMD;
				RAMWE = 1'b1;
				RAMCS = 1'b0;
				RAMOE = PSEN;
				ARDD_out = RAMD;
			end
							// Soren
			3'b010: begin
				RAMA = {0,P11,P10,BUSA[11:0]};
				RAMD_out = BUSD;
				BUSD_out = RAMD;
				RAMWE = 1'b1;
				RAMCS = 1'b0;
				RAMOE = PSEN;
				ARDD_out = RAMD;
			end
							// select game
			3'b011: 
			begin 
				ARDD_out = bankvp;
				RAMA = {1'b0,1'b0,P11,P10,BUSA[11],BUSA[9:0]};
				RAMD_out = BUSD;
				BUSD_out = RAMD;
				RAMWE = 1'b1;
				RAMCS = 1'b0;
				RAMOE = PSEN;
			end
							// XROM
			3'b101:
			begin
				RAMA = {1'b0,1'b0,1'b0,BUSA[11:0]};
				RAMD_out = BUSD;
				BUSD_out = RAMD;
				RAMWE = 1'b1;
				RAMCS = 1'b0;
				RAMOE = xromPSEN; // Así o invertido
				ARDD_out = RAMD;
			end
			3'b110: begin // Test
				RAMA = {ARDA[14:0]};
				RAMD_out = ARDD;
				case (ARDA[1:0])
					2'b00: begin
						ARDD_out = {T0,BUSD[0],BUSD[1],BUSD[2],BUSD[3],BUSD[4],BUSD[5],BUSD[6]};
					end
					2'b01: begin
						ARDD_out = {BUSD[7],BUSA[10],P14,P11,P10,BUSA[11],BUSA[9],1'b1};
					end
					2'b10: begin
						ARDD_out = {BUSA[8],BUSA[6],BUSA[7],BUSA[5],BUSA[4],BUSA[3],BUSA[2],BUSA[1]};
					end
					2'b11: begin
						ARDD_out = {BUSA[0],PSEN,EXTRAM,1'b1,1'b0,1'b0,BUSWR,1'b0};
//						ARDD_out = {1,0,1,0,1,0,1,0};
					end
				endcase 
				RAMWE = ARDWE;
				RAMCS = 1'b0;
				RAMOE = ARDOE;
				BUSD_out = RAMD;
			end
			3'b111,/*:  // BASIC MODULE
			begin
				ARDA[14] = T0; 								// T0
				ARDA[13] = BUSWR | P14 | BUSA[7]; 				// LE
				ARDA[12] = P10 | P11;						// RESET
				ARDA[11] = P11 | ~(EXTRAM & BUSA[7] & BUSA[5]);	// OE
				ARDD_out = BUSD;
				BUSD_out = ARDD;
			end*/
			3'b100:// sending game
			begin
				RAMA = {ARDA[14:0]};
				RAMD_out = ARDD;
				ARDD_out = RAMD;
				RAMWE = ARDWE;
				RAMCS = 1'b0;
				RAMOE = ARDOE;
				if (BUSA[0]==1'b0)
					BUSD_out = 8'h44; // 84 84
				else
					BUSD_out = 8'hC3; // 00 08
				// BUSD_out = RAMD; 
			end
		endcase
	end
	
	assign RAMD = (RAMWE == 1'b0)? RAMD_out:
						8'bZ;

//	assign BUSD = 	((xromPSEN==1'b0) && (PAGEMODE==3'b101)) ||
//						((PAGEMODE!=3'b101) && (PSEN == 1'b0))? BUSD_out:
//						8'bZ;

	assign BUSD_en = 	(PAGEMODE==3'b101)?	~xromPSEN:
							(PAGEMODE==3'b110)? 	1'b0:
							~PSEN;

	assign BUSD = 	BUSD_en? BUSD_out:
						8'bZ;
	assign ARDD = (ARDWE == 1'b1)? ARDD_out:
						8'bZ;
endmodule
